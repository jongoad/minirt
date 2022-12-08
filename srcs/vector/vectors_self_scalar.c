/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_self_scalar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:13:51 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 13:20:28 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Directly multiplies a vec3's components by a scalar */
void	mult_vec3_self(t_vec3 *v, double b)
{
	v->x *= b;
	v->y *= b;
	v->z *= b;
}

/* Directly divides a vec3's components by a scalar */
void	div_vec3_self(t_vec3 *v, double b)
{
	return (mult_vec3_self(v, 1.0f / b));
}

/* Directly transforms calling vector into unit vector (length == 1) */
void	unit_vec3_self(t_vec3 *v)
{
	double	is;

	is = 1 / sqrtf(
			v->x * v->x
			+ v->y * v->y
			+ v->z * v->z);
	return (mult_vec3_self(v, is));
}

/* Directly negates all components of the calling vector */
void	negate_vec3_self(t_vec3 *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}
