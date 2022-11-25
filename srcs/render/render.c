/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:18:56 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/25 16:23:07 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

bool	hit_anything(t_data *rt, t_ray *r, t_hit_rec *rec)
{
	int		i;

	i = -1;
	while (++i < rt->nb_objs)
	{
		if (rt->objs[i]->hit(r, rt->objs[i], rec))
		{
			rec->obj = rt->objs[i];
		}
	}
	return (rec->hit_anything);
}

static void	apply_textures(t_data *rt, t_hit_rec *rec)
{
	t_vec3	p;
	t_mat4	rot;

	if ((rt->toggle.is_texture || rt->toggle.is_normal)
		&& rec->obj->type == T_SPH)
	{
		p = sub_vec3(rec->p, rec->obj->pos);
		rot = mat_rot_compound(
				deg_to_rad(rec->obj->rot.x),
				deg_to_rad(rec->obj->rot.y),
				deg_to_rad(rec->obj->rot.z));
		p = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(p, T_POINT), rot));
		if ((rec->obj->texture.is_image || rec->obj->texture.is_checkers)
			&& rt->toggle.is_texture)
			rec->color = obj_get_color(rt, p, rec->obj);
		if (rt->toggle.is_normal && rec->obj->normal.is_image)
			rec->normal = obj_get_normal(rec->normal, p, rec->obj);
	}
}

/* Get final colour values for a single pixel */
static inline t_color	render_pixel(t_data *rt, t_ray *r, t_hit_rec *rec)
{
	register t_color	pixel_color;

	rec->t = T_MAX;
	rec->hit_anything = false;
	if (hit_anything(rt, r, rec))
	{
		apply_textures(rt, rec);
		pixel_color = pixel_shader(rt, rec, rec->color);
	}
	else
		pixel_color = rt->background;
	if (rt->toggle.is_light_halo)
		pixel_color = apply_light_halos(rt, r, rec, pixel_color);
	return (pixel_color);
}

/* Render current scene and displayto screen */
void	render_scene(t_data *rt)
{
	t_ray		r;
	t_hit_rec	rec;
	int			i;
	int			j;

	r.orig = rt->cam.pos;
	j = -1;
	while (++j < rt->img->height)
	{
		i = -1;
		while (++i < rt->img->width)
		{
			r.dir = rt->cam.rays[j][i];
			fill_pixel(rt->img, i, j, render_pixel(rt, &r, &rec));
		}
	}
	display_default(rt);
}
