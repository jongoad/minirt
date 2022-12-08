/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:21:25 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 14:15:20 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Create hit record for light rays */
int	hit_light(t_ray *r, t_obj *l, t_hit_rec *rec)
{
	l->fwd = r->dir;
	return (hit_plane(r, l, rec));
}

/* Check for intersections with light rays */
bool	hit_lights(t_data *rt, t_ray *r, t_hit_rec *rec)
{
	t_hit_rec	tmp;
	int			i;

	i = 0;
	tmp.t = T_MAX;
	tmp.hit_anything = false;
	while (i < rt->nb_lights)
	{
		rt->lights[i]->fwd = r->dir;
		rt->lights[i]->radius = LIGHT_RADIUS;
		if (hit_disk(r, rt->lights[i], &tmp))
		{
			if (length_vec3(sub_vec3(rt->lights[i]->pos, tmp.p)) < LIGHT_RADIUS)
			{
				*rec = tmp;
				rec->obj = rt->lights[i];
				tmp.hit_anything = true;
			}
			else
				tmp.t = T_MAX;
		}
		i++;
	}
	return (tmp.hit_anything);
}

/* Apply light halo effect based on ray-plane intersection */
t_color	apply_light_halos(t_data *rt, t_ray *r, t_hit_rec *rec, t_color color)
{
	t_hit_rec	rec2;
	int			i;
	float		dist;

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
