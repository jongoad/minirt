#include "minirt.h"

typedef struct s_shader
{
	t_ray	pt_to_light;	/* To calculate intersect with scene objects */
	t_hit_rec	rec;			/* To calculate hard shadows */
	t_color		ambient;		/* Ambient light */
	t_vec3		light_dir;		/* Normalized vector from intx_point to light */
	t_vec3		p_to_l;			/* Normalized vector from intx_point to light */
	t_vec3		view_dir;		/* Normalized vector from intx_point to camera */
	t_vec3		half_dir;		/* For Blinn-Phong model's specularity */
	t_vec3		light_color;	/* light.rgb converted to 0.0f-1.0f range */ // FIXME: move to light struct
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
	// Calculate light direction and view direction.
	// t_vec3	light_dir = (r->dir);
	// t_vec3	view_dir = unit_vec3(sub_vec3(rt->cam.pos, r->orig));
	// t_vec3 half_dir = unit_vec3(add_vec3(light_dir, view_dir));
    // double spec_angle = fmax(dot_vec3(half_dir, rec->normal), 0.0);
    // double specular = pow(spec_angle, SHININESS);
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
	shader->dist *= shader->dist;
	shader->light_color = div_vec3(color_to_vec3(light->clr), 255);

	shader->lambertian = fmax(dot_vec3(shader->pt_to_light.dir, rec->normal), 0.0F);

	shader->light_dir = shader->pt_to_light.dir;
	shader->view_dir = unit_vec3(sub_vec3(rt->cam.pos, shader->pt_to_light.orig));
	shader->half_dir = unit_vec3(add_vec3(shader->light_dir, shader->view_dir));
	shader->spec_angle = fmax(dot_vec3(shader->half_dir, rec->normal), 0.0);
	shader->specular = pow(shader->spec_angle, SHININESS);
	return (true);
}



/** 
 * 	Code for illumination found at:
 *  https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model
 */
t_color pixel_shader(t_data *rt, t_hit_rec *rec, t_color color)
{
	// t_ray		pt_to_light;
	// t_hit_rec		rec2;
	// t_vec3			light_color;
	// double			dist_to_light;
	// double			lambertian;
	static t_shader	shader;
	int				i;

	// color = color_x_vec3((t_color){255,255,255}, rt->ambient.scene_ambient);
	color = color_x_vec3(color, rt->ambient.scene_ambient);
	color.r = pow(color.r, 0.9F);
	color.g = pow(color.g, 0.9F);
	color.b = pow(color.b, 0.9F);
	i = -1;
	while (++i < rt->nb_lights)
	{
		// Diffuse lighting
		// pt_to_light.orig = rec->p;
		// pt_to_light.dir = sub_vec3(rt->lights[i]->pos, rec->p);
		if (calculate_shader_vars(rt, rec, &shader, rt->lights[i]) == false)
			continue ;

		// // Small optimization to fail the intersect early
		// if (dot_vec3(pt_to_light.dir, rec->normal) <= 0.0F)
		// 	continue;

		// // To verify objects hits are happening before light hit
		// dist_to_light = length_vec3(pt_to_light.dir);
		// rec2.t = dist_to_light;
		// // Normalize direction
		// unit_vec3_self(&pt_to_light.dir);
		
		// // Test for hard shadows, epsilon to prevent shadow acne
		// if (hit_anything(rt, &pt_to_light, &rec2) && fabs(rec2.t - dist_to_light) > EPSILON)
		// 	continue;
		
		// lambertian = fmax(dot_vec3(pt_to_light.dir, rec->normal), 0.0F);
		// dist_to_light *= dist_to_light;
		// light_color = div_vec3(color_to_vec3(rt->lights[i]->clr), 255);
		color = add_color(color, apply_diffuse(&shader, rec));
		color = add_color(color, apply_specular(&shader, rt->lights[i]));
	}
	return (color);
}
