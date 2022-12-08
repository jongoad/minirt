/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:14:20 by jgoad             #+#    #+#             */
/*   Updated: 2022/12/08 13:20:17 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Setup constant variables for camera */
void	cam_init(t_data *rt)
{
	rt->cam.up = vec3(0, 1, 0);
	rt->cam.is_move = false;
	/* Calculate viewport width based on FOV */
	rt->cam.view_w = 2 * tan(deg_to_rad(rt->cam.fov) / 2);
	/* Calculate viewport height based on viewport width */
	rt->cam.view_h = (rt->cam.view_w / ((float)ASPECT_RATIO * 100.0f)) * 100.0f;
	cam_recalc(rt);
}

/* Generate array of pre-cached rays */
void	cam_generate_rays(t_data *rt)
{
	t_i		i;
	t_vec4	ray;

	i.y = 0;
	while (i.y < IMG_H)
	{
		i.x = 0;
		while (i.x < IMG_W)
		{
			ray.x = (rt->cam.view_w * ((float)i.x / (float)IMG_W)) - (rt->cam.view_w * 0.5f);
			ray.y = (rt->cam.view_h * (1.0f - ((float)i.y / (float)IMG_H))) - (rt->cam.view_h * 0.5f);
			ray.z = -1.0f;
			ray.w = 0;
			ray = mat_mult_vec4(ray, rt->cam.m_pitch);
			ray = mat_mult_vec4(ray, rt->cam.m_yaw);
			rt->cam.rays[i.y][i.x] = unit_vec3(vec4_to_vec3(ray));
			i.x++;
		}
		i.y++;
	}
}

/* Recalculate camera data and regenerate ray cache */
void	cam_recalc(t_data *rt)
{
	rt->cam.m_pitch = mat_rot(deg_to_rad(rt->cam.pitch), 'x');
	rt->cam.m_yaw = mat_rot(deg_to_rad(rt->cam.yaw), 'y');
	rt->cam.forward = unit_vec3(vec4_to_vec3(mat_mult_vec4(
		mat_mult_vec4(vec4(0, 0, -1, 0),rt->cam.m_pitch), rt->cam.m_yaw)));
	rt->cam.right = unit_vec3(cross_vec3(rt->cam.forward, rt->cam.up));
	rt->cam.real_up = unit_vec3(cross_vec3(rt->cam.right, rt->cam.forward));
	cam_generate_rays(rt);
}
