/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:12:14 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 13:20:57 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Convert a vec3 to a vec4 */
t_vec4	vec3_to_vec4(t_vec3 input, char type)
{
	t_vec4	res;

	res.x = input.x;
	res.y = input.y;
	res.z = input.z;
	if (type == T_VEC)
		res.w = 0;
	else if (type == T_POINT)
		res.w = 1;
	return (res);
}

/* Convert a vec4 to a vec3 */
t_vec3	vec4_to_vec3(t_vec4 input)
{
	t_vec3	res;

	res.x = input.x;
	res.y = input.y;
	res.z = input.z;
	return (res);
}

/* Build a vec4 from four component float values */
t_vec4	vec4(float x, float y, float z, float w)
{
	t_vec4	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return (res);
}

/* Print vec3 data */
void	print_vec3(t_vec3 v)
{
	printf("(%f, %f, %f)", v.x, v.y, v.z);
}
