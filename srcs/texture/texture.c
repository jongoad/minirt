/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:15:14 by jgoad             #+#    #+#             */
/*   Updated: 2022/11/25 16:23:18 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Create a checkerboard pattern texture */
t_texture	uv_checkers(int width, int height, t_color c1, t_color c2)
{
	t_texture	res;

	res.width = width;
	res.height = height;
	res.c1 = c1;
	res.c2 = c2;
	res.is_image = false;
	res.is_checkers = true;
	return (res);
}

/* Return color at a given uv coordinate for checkerboard pattern */
t_color	uv_pattern_at_checkers(t_texture texture, t_vec2 uv)
{
	unsigned int	u;
	unsigned int	v;

	u = floor(uv.u * texture.width);
	v = floor(uv.v * texture.height);
	if ((u + v) % 2 == 0)
		return (texture.c1);
	else
		return (texture.c2);
}

/* Return colour at a given uv coordinate for texture image */
t_color	uv_pattern_at_image(t_texture texture, t_vec2 uv)
{
	unsigned int	u;
	unsigned int	v;

	u = floor((1 - uv.u) * (texture.width - 1));
	v = floor((1 - uv.v) * (texture.height - 1));
	return (texture.image.pixels[v][u]);
}

/* Get proper color value from a texture for a given point */
t_color	obj_get_color(t_data *rt, t_vec3 p, t_obj *obj)
{
	t_vec2	uv;

	if (rt->toggle.is_texture && obj->type == T_SPH)
	{
		uv = spherical_map(p);
		if (rt->toggle.is_texture && obj->texture.is_image)
			return (uv_pattern_at_image(obj->texture, uv));
		else if (rt->toggle.is_texture && obj->texture.is_checkers)
			return (uv_pattern_at_checkers(obj->texture, uv));
	}
	return (obj->clr);
}
