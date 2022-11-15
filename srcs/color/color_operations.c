/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:06:34 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 15:07:25 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Multiply color by a scale factor */
t_color	mult_color(t_color rgb, float factor)
{
	int	diff;

	diff = rgb.r * factor;
	rgb.r = diff;
	if (diff > 255)
		rgb.r = 255;
	else if (diff < 0)
		rgb.r = 0;
	diff = rgb.g * factor;
	rgb.g = diff;
	if (diff > 255)
		rgb.g = 255;
	else if (diff < 0)
		rgb.g = 0;
	diff = rgb.b * factor;
	rgb.b = diff;
	if (diff > 255)
		rgb.b = 255;
	else if (diff < 0)
		rgb.b = 0;
	return (rgb);
}

/* Add two color values together*/
t_color	add_color(t_color a, t_color b)
{
	int	diff;

	diff = a.r + b.r;
	a.r = diff;
	if (diff > 255)
		a.r = 255;
	else if (diff < 0)
		a.r = 0;
	diff = a.g + b.g;
	a.g = diff;
	if (diff > 255)
		a.g = 255;
	else if (diff < 0)
		a.g = 0;
	diff = a.b + b.b;
	a.b = diff;
	if (diff > 255)
		a.b = 255;
	else if (diff < 0)
		a.b = 0;
	return (a);
}

t_color	color_x_vec3(t_color col, t_vec3 factor)
{
	int	diff;

	diff = col.r * factor.x;
	col.r = diff;
	if (diff > 255)
		col.r = 255;
	else if (diff < 0)
		col.r = 0;
	diff = col.g * factor.y;
	col.g = diff;
	if (diff > 255)
		col.g = 255;
	else if (diff < 0)
		col.g = 0;
	diff = col.b * factor.z;
	col.b = diff;
	if (diff > 255)
		col.b = 255;
	else if (diff < 0)
		col.b = 0;
	return (col);
}
