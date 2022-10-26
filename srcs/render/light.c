#include "minirt.h"

int	apply_point_lights(t_data *rt, t_hit_rec *rec, int color)
{
	t_vec3		vcolor; 
	t_ray_vec3	pt_to_light;
	t_hit_rec	rec2;
	t_vec3		diff;
	double		diff_len;
	double		t;
	int			i;

	//FIXME: to remove
	i = -1;
	while (++i < rt->nb_lights)
	{
		pt_to_light.orig = rec->p;
		diff = sub_vec3(rt->lights[i]->pos, rec->p);
		pt_to_light.dir = diff;

		// To verify objects hits are happening before light hit
		diff_len = length_vec3(diff);
		rec2.t = diff_len;
		unit_vec3_self(&pt_to_light.dir);
		// Test for hard shadows, correct to prevent shadow acne
		if (hit_anything(rt, &pt_to_light, &rec2) && fabs(rec2.t - diff_len) > EPSILON)
			continue;
		t = cos_vec3(rec->normal, diff);
		t /= (diff_len + 1.0F);
		vcolor = int_to_vec3(color);
		color = vec3_to_color(lerp_vec3(vcolor, color_to_vec3(rt->lights[i]->clr), t));
	}
	return color;
}

bool	hit_light(t_ray_vec3 *r, t_obj *l, t_hit_rec *rec)
{	
	l->fwd = r->dir;
	return (hit_plane(r, l, rec));
}

int	apply_light_halos(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, int color)
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
			if (dist * dist < LIGHT_RADIUS
				&& (!rec->hit_anything || (rec->hit_anything && rec2.t < rec->t)))
				color = color_to_int(rt->lights[i]->clr);
			else if (rec->hit_anything == false || (dist * dist < LIGHT_RADIUS && rec2.t < rec->t))
				color = vec3_to_color(lerp_vec3(int_to_vec3(color), color_to_vec3(rt->lights[i]->clr), 1 / dist));
		}
	}
	return color;
}
