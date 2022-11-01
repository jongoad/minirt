#include "minirt.h"

t_color apply_specular(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, t_color color, t_obj *light)
{
	double	reflect_dot_view;

	// Calculate light direction and view direction.
	t_vec3 light_dir = (r->dir);
	t_vec3 view_dir = unit_vec3(sub_vec3(rt->cam.pos, rec->p));
    
    //Only if light is visible from the surface point.
        
	//Reflection vector around normal.
	t_vec3 reflectionDirection = reflect_ray(light_dir, rec->normal);
	// printf("reflectionDirection.length() = %.2f\n", length_vec3(reflectionDirection));

	reflect_dot_view = fmax(dot_vec3(reflectionDirection, view_dir), 0.0F);
	//Specular component.
	color = add_color(color, mult_color(light->clr, pow(reflect_dot_view, 20) * KS * LIGHT_INTENSITY * 10 / pow(length_vec3(sub_vec3(light->pos, rec->p)), 2)));
    
   	return (color);
}

t_color apply_point_lights(t_data *rt, t_hit_rec *rec, t_color color)
{
	t_ray_vec3 pt_to_light;
	t_hit_rec rec2;
	t_vec3	light_color;
	double dist_to_light;
	double t;
	double lambertian;
	double h;
	int i;

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
		h = length_vec3(project_a_on_b(pt_to_light.dir, rec->normal));
		// Normalize direction
		div_vec3_self(&pt_to_light.dir, dist_to_light);
		// Test for hard shadows, correct to prevent shadow acne
		if (hit_anything(rt, &pt_to_light, &rec2) && fabs(rec2.t - dist_to_light) > EPSILON)
			continue;
		t = cos_vec3(rec->normal, pt_to_light.dir);
		lambertian = fmax(dot_vec3(pt_to_light.dir, rec->normal), 0.0);
		// t *= LIGHT_INTENSITY;
		// t /= dist_to_light;
		dist_to_light *= dist_to_light;
		light_color = mult_vec3(color_to_vec3(rt->lights[i]->clr), 255);
		color = add_color(color, color_x_vec3(rec->color, mult_vec3(light_color, lambertian * LIGHT_INTENSITY / dist_to_light)));
		// color = add_color(color_x_vec3(color, rt->ambient.scene_ambient), lerp_color(rec->color, mult_color(rt->lights[i]->clr, t / dist_to_light), t));
		// color = lerp_color(color, rt->lights[i]->clr, t);
		color = apply_specular(rt, &pt_to_light, rec, color, rt->lights[i]);
	}
	// return (color_x_vec3(color, rt->ambient.scene_ambient));
	// if (!hit)
	// 	return (color_x_vec3(color, rt->ambient.scene_ambient));
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
