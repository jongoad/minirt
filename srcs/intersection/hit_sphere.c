/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:21:45 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 14:16:07 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Check for ray intersection with sphere objects */
int	hit_sphere(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	register t_vec3			oc;
	static t_quadratic		q;

	oc = sub_vec3(r->orig, o->pos);
	q.a = dot_vec3(r->dir, r->dir);
	q.half_b = dot_vec3(oc, r->dir);
	q.c = dot_vec3(oc, oc) - o->radius * o->radius;
	q.discriminant = q.half_b * q.half_b - q.a * q.c;
	if (q.discriminant < 0 || q.a == 0)
		return (0);
	q.sqrtd = sqrtf(q.discriminant);
	q.root = (-q.half_b - q.sqrtd) / q.a;
	if (q.root < T_MIN || q.root > rec->t)
	{
		q.root = (-q.half_b + q.sqrtd) / q.a;
		if (q.root < T_MIN || q.root > rec->t)
			return (0);
		rec->inside_surface = true;
	}
	rec->hit_anything = true;
	rec->t = q.root;
	rec->p = ray_at(r, rec->t);
	rec->normal = div_vec3(sub_vec3(rec->p, o->pos), o->radius);
	rec->color = o->clr;
	return (1);
}
