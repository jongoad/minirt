#include "minirt.h"

t_color	apply_point_lights(t_data *rt, t_hit_rec *rec, t_color color)
{
	t_ray_vec3	pt_to_light;
	t_hit_rec	rec2;
	double		dist_to_light;
	double		t;
	int			i;

	i = -1;
	while (++i < rt->nb_lights)
	{
		// Diffuse lighting
		pt_to_light.orig = rec->p;
		pt_to_light.dir = sub_vec3(rt->lights[i]->pos, rec->p);

		// Small optimization to fail check early
		if (dot_vec3(pt_to_light.dir, rec->normal) <= 0.0F)
			continue ;

		// To verify objects hits are happening before light hit
		dist_to_light = length_vec3(pt_to_light.dir);
		rec2.t = dist_to_light;
		unit_vec3_self(&pt_to_light.dir);
		// Test for hard shadows, correct to prevent shadow acne
		if (hit_anything(rt, &pt_to_light, &rec2) && fabs(rec2.t - dist_to_light) > EPSILON)
			continue ;
		// t = cos_vec3(rec->normal, pt_to_light.dir);
		t = cos_vec3(rec->normal, pt_to_light.dir) * LIGHT_INTENSITY;
		t /= (dist_to_light + 1.0F);
		color = lerp_color(color, rt->lights[i]->clr, t);


		// Specular reflection

	}
	return (color);
}

bool	hit_light(t_ray_vec3 *r, t_obj *l, t_hit_rec *rec)
{	
	l->fwd = r->dir;
	return (hit_plane(r, l, rec));
}

t_color	apply_light_halos(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, t_color color)
{
	t_hit_rec		rec2;
	int				i;
	float			dist;
	
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
