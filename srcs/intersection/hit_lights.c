#include "minirt.h"

bool hit_light(t_ray *r, t_obj *l, t_hit_rec *rec)
{
	l->fwd = r->dir;
	return (hit_plane(r, l, rec));
}

bool hit_lights(t_data *rt, t_ray *r, t_hit_rec *rec)
{
	double	tmp;
	int		i;

	i = 0;
	tmp = rec->t;
	while (i < rt->nb_lights)
	{
		if (hit_light(r, rt->lights[i], rec))
		{
			if (length_vec3(sub_vec3(rt->lights[i]->pos, rec->p)) < LIGHT_RADIUS)
				rec->obj = rt->lights[i];
			else
				rec->t = tmp;
		}
		i++;
	}
	return (rec->hit_anything);
}


t_color apply_light_halos(t_data *rt, t_ray *r, t_hit_rec *rec, t_color color)
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
