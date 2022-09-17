/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismaelyahyaouiracine <ismaelyahyaouirac    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:11:16 by jgoad             #+#    #+#             */
/*   Updated: 2022/09/17 18:18:08 by ismaelyahya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Create identity matrix */
float **matrix_identity(int fill, int fill_diagonal)
{
	float	**m;
	t_i		i;

	m = (float **)ft_xalloc(sizeof(float *) * 4);
	i.y = 0;
	while (i.y < 4)
	{
		m[i.y] = (float *)ft_xalloc(sizeof(float) * 4);
		i.x = 0;
		while (i.x < 4)
		{
			if (i.x == i.y)
				m[i.y][i.x] = fill_diagonal;
			else
				m[i.y][i.x] = fill; 
			i.x++;
		}
		i.y++;
	}
	return (m);
}

/* Create rotation matrix */
float	**matrix_rotation(float x, char axis)
{
	float **m;

	m = matrix_identity(0, 1); //Initialize matrix
	if (!m)
		return (0);
	if (axis == 'x') //If rotation axis is x
	{
		m[1][1] = cos(x);
		m[1][2] = sin(x);
		m[2][1] = -sin(x);
		m[2][2] = cos(x);
	}
	else if (axis == 'y') //If rotation axis is y
	{
		m[0][0] = cos(x);
		m[0][2] = -sin(x);
		m[2][0] = sin(x);
		m[2][2] = cos(x);
	}
	else if (axis == 'z') //If rotation axis is x
	{
		m[0][0] = cos(x);
		m[0][1] = sin(x);
		m[1][0] = -sin(x);
		m[1][1] = cos(x);
	}
	return (m);	
}

/* Create scale matrix */
float	**matrix_scale(t_point scale)
{
	float	**m;

	m = matrix_identity(0, 1);
	if (!m)
		return (0);
	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
	m[3][3] = scale.w;
	return (m);
}

/* Create translation matrix */
float	**matrix_translate(t_point translate)
{
	float	**m;

	m = matrix_identity(0, 1);
	if (!m)
		return (0);
	m[0][3] = translate.x;
	m[1][3] = translate.y;
	m[2][3] = translate.z;
	return (m);
}

/* Multiply two matrices together */
float	**matrix_mult_mat(float **m1, float **m2)
{
	float **m3; //Declare output matrix
	t_i i;

	m3 = matrix_identity(0, 1); //Init output matrix
	i.y = 0;
	while (i.y < 4)
	{
		i.x = 0;
		while (i.x < 4)
		{
			m3[i.y][i.x] = (m1[i.y][0] * m2[0][i.x]) + 
						   (m1[i.y][1] * m2[1][i.x]) +
						   (m1[i.y][2] * m2[2][i.x]) +
						   (m1[i.y][3] * m2[3][i.x]);
			i.x++;
		}
		i.y++;
	}
	return (m3);
}

/* Multiply a point by a matrix */
void	matrix_mult_point(t_point *v, float **mat)
{
	t_point tmp;

	//Hold temp values
	tmp.x = (*v).x;
	tmp.y = (*v).y;
	tmp.z = (*v).z;
	tmp.w = (*v).w;

	//Multiply vertex by matrix
	v->x = (tmp.x * mat[0][0]) + (tmp.y * mat[0][1]) + (tmp.z * mat[0][2]) + (tmp.w * mat[0][3]);
	v->y = (tmp.x * mat[1][0]) + (tmp.y * mat[1][1]) + (tmp.z * mat[1][2]) + (tmp.w * mat[1][3]);
	v->z = (tmp.x * mat[2][0]) + (tmp.y * mat[2][1]) + (tmp.z * mat[2][2]) + (tmp.w * mat[2][3]);
	v->w = (tmp.x * mat[3][0]) + (tmp.y * mat[3][1]) + (tmp.z * mat[3][2]) + (tmp.w * mat[3][3]);
}

// //Apply a matrix to all vertices in model (add free function here?)
// void	apply_matrix(t_data *d, float **mat)
// {
// 	t_i i;

// 	i.y = 0;
// 	while (i.y < d->model.max.y)
// 	{
// 		i.x = 0;
// 		while (i.x < d->model.max.x)
// 		{
// 			matrix_mult_vertex(&d->model.m[i.y][i.x], mat);
// 			i.x++;
// 		}
// 		i.y++;
// 	}
// }

/* Free a matrix */
void	matrix_free(float **mat)
{
	t_i i;

	i.y = 0;
	while (i.y < 3)
	{
		free(mat[i.y]);
	}
	free(mat);
}
