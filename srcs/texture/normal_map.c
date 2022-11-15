/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:15:00 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/15 15:15:00 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Find UV coordinate at a point for a given object type */
t_vec2	uv_at(t_vec3 p, t_obj *obj)
{
	t_vec2	uv;

	if (obj->type == T_SPH)
		uv = spherical_map(p);
	else if (obj->type == T_PLANE)
		uv = planar_map(p);
	else if (obj->type == T_CYL)
		uv = cylindrical_map(p);
	else if (obj->type == T_CONE)
		uv = cylindrical_map(p);
	uv.u = floor((1.0f - uv.u) * (obj->texture.width - 1));
	uv.v = floor((1.0f - uv.v) * (obj->texture.height - 1));
	return (uv);
}

/* Get normal vector from normal map image */
t_vec3	get_normal_map(t_vec3 p, t_obj *obj)
{
	t_vec3			normal;
	t_vec2			pos;
	unsigned int	u;
	unsigned int	v;

	pos = spherical_map(p);
	u = floor((1.0f - pos.u) * (obj->normal.width - 1));
	v = floor((1.0f - pos.v) * (obj->normal.height - 1));
	normal.x = (((float)obj->normal.image.pixels[v][u].r / 255.0f)
			* 2.0f) - 1.0f;
	normal.y = (((float)obj->normal.image.pixels[v][u].g / 255.0f)
			* 2.0f) - 1.0f;
	normal.z = (((float)obj->normal.image.pixels[v][u].b / 255.0f)
			* 2.0f) - 1.0f;
	return (unit_vec3(normal));
}

/* Create new normal vector using normal map */
t_vec3	obj_get_normal(t_vec3 normal, t_vec3 p, t_obj *obj)
{
	t_vec3	perturb;
	t_vec3	new_up;
	t_vec3	p_v;
	t_vec3	p_u;
	t_vec3	res;

	perturb = get_normal_map(p, obj);
	if (normal.y > 0.99f || normal.y < -0.99f)
		new_up = vec3(1, 0, 0);
	else
		new_up = vec3(0, 1, 0);
	p_v = unit_vec3(cross_vec3(new_up, normal));
	p_u = unit_vec3(cross_vec3(normal, p_v));
	res = add_vec3(normal, mult_vec3(p_u, perturb.x));
	res = add_vec3(res, mult_vec3(p_v, perturb.y));
	res = add_vec3(res, mult_vec3(normal, perturb.z));
	res = unit_vec3(res);
	return (res);
}
