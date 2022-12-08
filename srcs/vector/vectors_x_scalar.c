/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_x_scalar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:11:16 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 13:21:19 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Multiplies a vector with a scalar */
t_vec3	mult_vec3(t_vec3 v, double b)
{
	return (vec3(
			v.x * b,
			v.y * b,
			v.z * b));
}

/* Divides a vector with a scalar */
t_vec3	div_vec3(t_vec3 v, double b)
{
	if (b == 0)
		return (v);
	return (mult_vec3(v, 1.0f / b));
}

/* Gives you the length of a given vector */
double	length_vec3(t_vec3 v)
{
	return (sqrtf(
			(v.x) * (v.x)
			+ (v.y) * (v.y)
			+ (v.z) * (v.z)));
}

/* Negates all components of a vec3 */
t_vec3	negate_vec3(t_vec3 v)
{
	return (vec3(-v.x, -v.y, -v.z));
}

/* Transforms a given vector into a unit vector (length == 1) */
t_vec3	unit_vec3(t_vec3 v)
{
	double	is;

	is = (1 / sqrtf(
				(v.x) * (v.x)
				+ (v.y) * (v.y)
				+ (v.z) * (v.z)));
	return (mult_vec3(v, is));
}
