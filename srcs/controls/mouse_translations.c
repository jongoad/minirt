/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:16 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 14:54:24 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "hooks.h"

int	handle_mouse_xy_translation(float pcnt_x, float pcnt_y, t_data *rt)
{
	float	z_dist;

	if (rt->toggle.is_left_click && rt->selected && pcnt_x != 0 && pcnt_y != 0)
	{
		z_dist = length_vec3(
				project_a_on_b(
					sub_vec3(rt->selected->pos, rt->cam.pos), rt->cam.forward));
		add_vec3_self(&rt->selected->pos,
			mult_vec3(rt->cam.right, rt->cam.view_w * pcnt_x * z_dist));
		add_vec3_self(&rt->selected->pos,
			mult_vec3(rt->cam.real_up, rt->cam.view_h * -pcnt_y * z_dist));
		render_scene(rt);
		return (true);
	}
	return (false);
}

int	handle_mouse_z_translation(t_data *rt, int button)
{
	float	z_offset;

	if (rt->selected)
	{
		if (button == WHEEL_UP)
			z_offset = 1.0F;
		else
			z_offset = -1.0F;
		add_vec3_self(&rt->selected->pos,
			mult_vec3(rt->cam.forward, z_offset));
		render_scene(rt);
		return (true);
	}
	return (false);
}
