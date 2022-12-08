/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:21:19 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 13:49:23 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Cache quadratic solver data for current object */
static bool	cylinder_quadratic(t_ray *r, t_obj *o, t_quadratic *q)
{
	q->oc = sub_vec3(r->orig, o->pos);
	q->dir_dot_fwd = dot_vec3(r->dir, o->fwd);
	q->oc_dot_fwd = dot_vec3(q->oc, o->fwd);
	q->a = dot_vec3(r->dir, r->dir) - q->dir_dot_fwd * q->dir_dot_fwd;
	q->half_b = dot_vec3(r->dir, q->oc) - q->dir_dot_fwd * q->oc_dot_fwd;
	q->c = dot_vec3(q->oc, q->oc) - q->oc_dot_fwd * q->oc_dot_fwd - o->radius * o->radius;
	q->discriminant = q->half_b * q->half_b - q->a * q->c;
	if (q->discriminant < 0)
		return (false);
	q->sqrtd = sqrtf(q->discriminant);
	q->root = (-q->half_b - q->sqrtd) / q->a;
	return (true);
}

/* Calculate ray-object intersection for cylinder body */
int	hit_cylinder_body(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	static t_quadratic		q;
	double					dist;

	if (cylinder_quadratic(r, o, &q) == false)
		return (false);
	dist = q.dir_dot_fwd * q.root + q.oc_dot_fwd;
	if (q.root < T_MIN || q.root > rec->t || fabs(dist) > o->half_height)
	{
		q.root = (-q.half_b + q.sqrtd) / q.a;
		dist = q.dir_dot_fwd * q.root + q.oc_dot_fwd;
		if (q.root < T_MIN || q.root >= rec->t || fabs(dist) > o->half_height)
			return (false);
		rec->inside_surface = true;
	}
	rec->hit_anything = true;
	rec->t = q.root;
	rec->p = ray_at(r, rec->t);
	rec->color = o->clr;
	rec->normal = unit_vec3(
			sub_vec3(
				sub_vec3(rec->p, o->pos),
				mult_vec3(o->fwd, dist)));
	return (true);
}

/* Check for ray-object intersection for a cylinder object */
int	hit_cylinder(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	int	hit;

	hit = 0;
	hit += hit_caps(r, o, rec);
	hit += hit_cylinder_body(r, o, rec);
	return (hit);
}
