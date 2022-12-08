/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:16 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 13:41:19 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "hooks.h"

/* Print object selection data to terminal */
static void	print_selected_object_info(t_data *rt)
{
	if (rt->selected == NULL)
	{
		printf("Click on a scene object to select it.\n");
		return ;
	}
	printf("You have selected a ");
	if (rt->selected->type == T_CYL)
		printf("cylinder.");
	else if (rt->selected->type == T_PLANE)
		printf("plane.");
	else if (rt->selected->type == T_SPH)
		printf("sphere.");
	else if (rt->selected->type == T_LIGHT)
		printf("point light.");
	else
		printf("mysterious object...");
	printf("(Press `F1' to display keyboard controls)\n");
}

/* Mouse button release hooks handling */
int	handle_mouse_btn_release(int button, int x, int y, t_data *rt)
{
	(void)rt;
	(void)x;
	(void)y;
	if (button == RIGHT_CLICK)
		rt->cam.is_move = false;
	else if (button == 1)
		rt->toggle.is_left_click = false;
	return (0);
}

/* Mouse button press hooks handling */
int	handle_mouse_hook(int button, int x, int y, t_data *rt)
{
	(void)rt;
	(void)x;
	(void)y;
	/* Cast a ray for current pixel on mouse left click to select an object */
	if (button == LEFT_CLICK)
	{
		rt->selected = cast_ray_at_pixel(rt, x, y);
		print_selected_object_info(rt);
		rt->toggle.is_left_click = true;
	}
	else if (button == RIGHT_CLICK)
		rt->cam.is_move = true;
	else if (button == WHEEL_UP || button == WHEEL_DOWN)
		handle_mouse_z_translation(rt, button);
	else
		return (0);
	rt->cam.prev_mouse = vec3((float)x, (float)y, 0);
	return (0);
}

/* Mouse movement hooks control */
int	handle_mouse_motion(int x, int y, t_data *rt)
{
	t_vec3	cur_mouse;
	t_vec3	pcnt;

	cur_mouse = vec3((float)x, (float)y, 0);
	pcnt.x = (float)(cur_mouse.x - rt->cam.prev_mouse.x) / (float)IMG_W;
	pcnt.y = (float)(cur_mouse.y - rt->cam.prev_mouse.y) / (float)IMG_H;
	if (rt->cam.is_move && (pcnt.x != 0 || pcnt.y != 0))
	{
		rt->cam.pitch += pcnt.y * CAM_ROT_RATE;
		if (rt->cam.pitch > CAM_MAX_TILT)
			rt->cam.pitch = CAM_MAX_TILT;
		else if (rt->cam.pitch < -CAM_MAX_TILT)
			rt->cam.pitch = -CAM_MAX_TILT;
		rt->cam.yaw += pcnt.x * CAM_ROT_RATE;
		if (rt->cam.yaw < 0)
			rt->cam.yaw = (int)rt->cam.yaw % 360;
		else if (rt->cam.yaw > 0)
			rt->cam.yaw = (int)rt->cam.yaw % -360;
		rt->cam.prev_mouse = cur_mouse;
		cam_recalc(rt);
		render_scene(rt);
	}
	if (handle_mouse_xy_translation(pcnt.x, pcnt.y, rt))
		rt->cam.prev_mouse = vec3((float)x, (float)y, 0);
	return (0);
}
