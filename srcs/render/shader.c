#include "minirt.h"

typedef struct s_shader
{
	t_ray		pt_to_light;	/* To calculate intersect with scene objects */
	t_hit_rec	rec;			/* To calculate hard shadows */
	t_color		ambient;		/* Ambient light */
	t_vec3		light_dir;		/* Normalized vector from intx_point to light */
	t_vec3		p_to_l;			/* Normalized vector from intx_point to light */
	t_vec3		view_dir;		/* Normalized vector from intx_point to camera */
	t_vec3		half_dir;		/* For Blinn-Phong model's specularity */
	t_vec3		light_color;	/* light.rgb converted to 0.0f-1.0f range */
	double		dist;			/* Dist from hit_point to light */
	double		specular;		/* Final specular contribution to shader */
	double		spec_angle;		/* Angle between view_dir and light_dir, calculated from half_dir */
	double		lambertian;		/* Final lambertian contribution to shader */
}	t_shader;


static inline t_color	apply_diffuse(t_shader *shader, t_hit_rec *rec)
{
	return (color_x_vec3(rec->color, \
		mult_vec3( \
			shader->light_color, \
			shader->lambertian * KD / shader->dist)));
}

static inline t_color	apply_specular(t_shader *shader, t_obj *light)
{
	return (mult_color(light->clr, shader->specular * KS / shader->dist));
}

static inline bool	calculate_shader_vars(t_data *rt, t_hit_rec *rec, t_shader *shader, t_obj *light)
{
	shader->pt_to_light.orig = rec->p;
	shader->pt_to_light.dir = sub_vec3(light->pos, rec->p);

	// Small optimization to fail the intersect early
	if (dot_vec3(shader->pt_to_light.dir, rec->normal) <= 0.0F)
		return (false);

	// Calculate the bare minimum to test for shadows
	shader->dist = length_vec3(shader->pt_to_light.dir);
	shader->rec.t = shader->dist;
	unit_vec3_self(&shader->pt_to_light.dir);

	// Test for hard shadows, epsilon to prevent shadow acne
	if (hit_anything(rt, &shader->pt_to_light, &shader->rec) \
		&& fabs(shader->rec.t - shader->dist) > EPSILON)
		return (false);
	
	// For both diffuse and specular
	shader->dist += 1.0F;
	shader->dist *= shader->dist;
	shader->light_color = div_vec3(color_to_vec3(light->clr), 255);

	shader->lambertian = fmax(dot_vec3(shader->pt_to_light.dir, rec->normal), 0.0F);

	shader->light_dir = shader->pt_to_light.dir;
	shader->view_dir = unit_vec3(sub_vec3(rt->cam.pos, shader->pt_to_light.orig));
	shader->half_dir = unit_vec3(add_vec3(shader->light_dir, shader->view_dir));
	shader->spec_angle = fmax(dot_vec3(shader->half_dir, rec->normal), 0.0F);
	shader->specular = pow(shader->spec_angle, rec->obj->shininess);
	//FIXME - Ensure that using per object shininess is fine (will this interact with halos?)
	return (true);
}

/** 
 * 	Code for illumination found at:
 *  https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model
 */
t_color pixel_shader(t_data *rt, t_hit_rec *rec, t_color color)
{
	static t_shader	shader;
	int				i;

	color = color_x_vec3(color, rt->ambient.scene_ambient);
	color.r = pow(color.r, 0.9F);
	color.g = pow(color.g, 0.9F);
	color.b = pow(color.b, 0.9F);
	i = -1;
	// return ((t_color){rec->normal.x * 255,  rec->normal.y * 255, rec->normal.z * 255});
	while (++i < rt->nb_lights)
	{
		if (calculate_shader_vars(rt, rec, &shader, rt->lights[i]) == false)
			continue ;
		color = add_color(color, apply_diffuse(&shader, rec));
		if (rt->toggle.is_specular)
			color = add_color(color, apply_specular(&shader, rt->lights[i]));
	}
	return (color);
}
