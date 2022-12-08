/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:21:41 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 14:15:46 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Check for ray intersection with plane objects */
int	hit_plane(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	register float	discriminant;
	register float	t;

	discriminant = dot_vec3(o->fwd, r->dir);
	t = dot_vec3(sub_vec3(o->pos, r->orig), o->fwd) / discriminant;
	if (t < T_MIN || t >= rec->t)
		return (false);
	rec->t = t;
	rec->hit_anything = true;
	rec->color = o->clr;
	rec->normal = o->fwd;
	rec->p = ray_at(r, rec->t);
	return (true);
}
