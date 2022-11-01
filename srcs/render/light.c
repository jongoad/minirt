#include "minirt.h"

t_color apply_specular(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, t_obj *light)
{
	// Calculate light direction and view direction.
	t_vec3	light_dir = (r->dir);
	t_vec3	view_dir = unit_vec3(sub_vec3(rt->cam.pos, r->orig));
    

	t_vec3 halfDir = unit_vec3(add_vec3(light_dir, view_dir));
    double specAngle = fmax(dot_vec3(halfDir, rec->normal), 0.0);
    double specular = pow(specAngle, SHININESS);
	return (mult_color(light->clr, specular * KS * LIGHT_INTENSITY / pow(length_vec3(sub_vec3(light->pos, r->orig)), 2)));
}

/**
 * 	Code for illumination found at:
 *  https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model
 */
t_color apply_point_lights(t_data *rt, t_hit_rec *rec, t_color color)
{
	t_ray_vec3	pt_to_light;
	t_hit_rec	rec2;
	t_vec3		light_color;
	double		dist_to_light;
	double		lambertian;
	int			i;

	color = color_x_vec3(color, rt->ambient.scene_ambient);
	i = -1;
	while (++i < rt->nb_lights)
	{
		// Diffuse lighting
		pt_to_light.orig = rec->p;
		pt_to_light.dir = sub_vec3(rt->lights[i]->pos, rec->p);

		// Small optimization to fail the intersect early
		if (dot_vec3(pt_to_light.dir, rec->normal) <= 0.0F)
			continue;

		// To verify objects hits are happening before light hit
		dist_to_light = length_vec3(pt_to_light.dir);
		rec2.t = dist_to_light;
		// Normalize direction
		unit_vec3_self(&pt_to_light.dir);
		
		// Test for hard shadows, epsilon to prevent shadow acne
		if (hit_anything(rt, &pt_to_light, &rec2) && fabs(rec2.t - dist_to_light) > EPSILON)
			continue;
		
		lambertian = fmax(dot_vec3(pt_to_light.dir, rec->normal), 0.0F);
		dist_to_light *= dist_to_light;
		light_color = div_vec3(color_to_vec3(rt->lights[i]->clr), 255);
		color = add_color(color, color_x_vec3(rec->color, mult_vec3(light_color, lambertian * KD * LIGHT_INTENSITY / dist_to_light)));
		color = add_color(color, apply_specular(rt, &pt_to_light, rec, rt->lights[i]));
	}
	return (color);
}

bool hit_light(t_ray_vec3 *r, t_obj *l, t_hit_rec *rec)
{
	l->fwd = r->dir;
	return (hit_plane(r, l, rec));
}

t_color apply_light_halos(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, t_color color)
{
	t_hit_rec rec2;
	int i;
	float dist;

	(void)rec;
	i = -1;
	while (++i < rt->nb_lights)
	{
		rec2.t = T_MAX;
		rec2.hit_anything = false;
		if (hit_light(r, rt->lights[i], &rec2))
		{
			dist = length_vec3(sub_vec3(rt->lights[i]->pos, rec2.p));
			dist += 1.0F;
			dist *= dist;
			color = lerp_color(color, rt->lights[i]->clr, 1 / dist);
		}
	}
	return (color);
}
