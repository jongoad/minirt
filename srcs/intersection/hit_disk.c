/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:21:22 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 14:21:22 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_disk(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	register float	discriminant;
	register float	t;
	register t_vec3	p;

	discriminant = dot_vec3(o->fwd, r->dir);
	t = dot_vec3(sub_vec3(o->pos, r->orig), o->fwd) / discriminant;
	p = ray_at(r, t);
	if (t < T_MIN || t >= rec->t \
			|| length_vec3(sub_vec3(p, o->pos)) > o->radius)
		return (false);
	rec->t = t;
	rec->hit_anything = true;
	rec->color = o->clr;
	rec->normal = o->fwd;
	rec->p = ray_at(r, rec->t);
	return (true);
}
