/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:11:16 by jgoad             #+#    #+#             */
/*   Updated: 2022/10/07 14:09:14 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Create identity matrix */
void	mat_id(t_mat4 *m)
{
	t_i		i;

	i.y = 0;
	while (i.y < 4)
	{
		i.x = 0;
		while (i.x < 4)
		{
			if (i.x == i.y)
				m->m[i.y][i.x] = 1;
			else
				m->m[i.y][i.x] = 0; 
			i.x++;
		}
		i.y++;
	}
}

/* Create scale matrix */
t_mat4	mat_scale(t_vec4 scale)
{
	t_mat4	m;

	mat_id(&m);
	m.m[0][0] = scale.x;
	m.m[1][1] = scale.y;
	m.m[2][2] = scale.z;
	m.m[3][3] = scale.w;
	return (m);
}

/* Create rotation matrix */
t_mat4	mat_rot(float x, char axis)
{
	t_mat4	m;

	mat_id(&m);
	if (axis == 'x') //If rotation axis is x
	{
		m.m[1][1] = cos(x);
		m.m[1][2] = sin(x);
		m.m[2][1] = -sin(x);
		m.m[2][2] = cos(x);
	}
	else if (axis == 'y') //If rotation axis is y
	{
		m.m[0][0] = cos(x);
		m.m[0][2] = -sin(x);
		m.m[2][0] = sin(x);
		m.m[2][2] = cos(x);
	}
	else if (axis == 'z') //If rotation axis is x
	{
		m.m[0][0] = cos(x);
		m.m[0][1] = sin(x);
		m.m[1][0] = -sin(x);
		m.m[1][1] = cos(x);
	}
	return (m);	
}

/* Create translation matrix */
t_mat4	mat_trans(t_vec4 trans)
{
	t_mat4	m;

	mat_id(&m);
	m.m[0][3] = trans.x;
	m.m[1][3] = trans.y;
	m.m[2][3] = trans.z;
	m.m[3][3] = trans.w;

	return (m);
}

