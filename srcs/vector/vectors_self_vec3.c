/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_self_vec3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:13:45 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 14:13:46 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Directly add a vec3's components to the calling vec3 */
void	add_vec3_self(t_vec3 *a, t_vec3 b)
{
		a->x += b.x;
		a->y += b.y;
		a->z += b.z;
}

/* Directly adds 2 vec3's components to the calling vec3 */
void	add3_vec3_self(t_vec3 *a, t_vec3 b, t_vec3 c)
{
		a->x += b.x + c.x;
		a->y += b.y + c.y;
		a->z += b.z + c.z;
}

/* Directly subs a vec3's components from the calling vec3 */
void	sub_vec3_self(t_vec3 *a, t_vec3 b)
{
		a->x -= b.x;
		a->y -= b.y;
		a->z -= b.z;
}

/* Directly multiplies a vec3's components by the calling vec3's components */
void	mult_vec3_vec3_self(t_vec3 *a, t_vec3 b)
{
		a->x *= b.x;
		a->y *= b.y;
		a->z *= b.z;
}

/* Directly transforms calling vector into its cross product with 2nd vector */
void	cross_vec3_self(t_vec3 *a, t_vec3 b)
{
	a->x = (a->y * b.z) - (a->z * b.y);
	a->y = (a->z * b.x) - (a->x * b.z);
	a->z = (a->x * b.y) - (a->y * b.x);
}
