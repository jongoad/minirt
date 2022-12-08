/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:57:52 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/12/08 13:40:24 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "hooks.h"

/* Key release event hooks */
int	handle_key_release_hook(int keysym, t_data *rt)
{
	if (keysym == KEY_ESC)
		rt_clean_exit(rt);
	if (keysym == KEY_L)
		rt->toggle.is_light_halo = !(rt->toggle.is_light_halo);
	else if (keysym == KEY_N)
		rt->toggle.is_normal = !(rt->toggle.is_normal);
	else if (keysym == KEY_T)
		rt->toggle.is_texture = !(rt->toggle.is_texture);
	else if (keysym == KEY_F1)
		print_usage();
	else
		return (0);
	render_scene(rt);
	return (0);
}

/* Key press event hooks */
int	handle_key_press_hook(int keysym, t_data *rt)
{
	/* Handle camera keyboard movement (while RMB held down) */
	if (rt->cam.is_move)
	{
		if (keysym == KEY_W)	/* Forward on z-axis */
			add_vec3_self(&rt->cam.pos, mult_vec3(rt->cam.forward, CAM_TRANS));
		if (keysym == KEY_S)	/* Backwards on z-axis */
			sub_vec3_self(&rt->cam.pos, mult_vec3(rt->cam.forward, CAM_TRANS));
		if (keysym == KEY_A)	/* Left on x-axis */
			sub_vec3_self(&rt->cam.pos, mult_vec3(rt->cam.right, CAM_TRANS));
		if (keysym == KEY_D)	/* Right on x-axis */
			add_vec3_self(&rt->cam.pos, mult_vec3(rt->cam.right, CAM_TRANS));
		if (keysym == KEY_Q)	/* Down on y-axis */
			sub_vec3_self(&rt->cam.pos, mult_vec3(rt->cam.real_up, CAM_TRANS));
		if (keysym == KEY_E)	/* Up on y-axis */
			add_vec3_self(&rt->cam.pos, mult_vec3(rt->cam.real_up, CAM_TRANS));
		cam_recalc(rt);
		render_scene(rt);
	}
	/* Hand individual object keyboard movement */
	else if (rt->selected != NULL)
	{
		if (keysym == KEY_SPACE)
			print_obj_data(rt->selected);
		handle_object_translations(keysym, rt);
		handle_object_rotations(keysym, rt);
	}
	return (0);
}

/* Apply scale transformation to specified object */
void	apply_object_scale(t_obj *o, bool is_positive)
{
	if (is_positive)
		o->scale *= 1.1;
	else
	{
		o->scale /= 1.1;
		/* Clamp minimum scale value to (0.1 * original value) */
		if (o->scale > 0.1)
			o->scale = 0.1;
	}
	/* Apply scale properly per object type */
	if (o->type == T_SPH || o->type == T_CYL)
		o->radius = o->ref_radius * o->scale;
	if (o->type == T_CYL || o->type == T_CONE)
		o->half_height = o->ref_half_height * o->scale;
	if (o->type == T_CONE)
		o->radius = tanf(o->angle) * o->half_height;
}

/* Object translation keyhook handling */
int	handle_object_translations(int keysym, t_data *rt)
{
	t_obj	*o;

	o = rt->selected;
	if (keysym == KEY_W)	/* Forward on z-axis */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.forward, 2.0F));
	else if (keysym == KEY_S)	/* Backwards on z-axis */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.forward, 2.0F));
	else if (keysym == KEY_LEFT || keysym == KEY_A)	/* Left on x-axis */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.right, 2.0F));
	else if (keysym == KEY_RIGHT || keysym == KEY_D)	/* Right on x-axis */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.right, 2.0F));
	else if (keysym == KEY_UP || keysym == KEY_E)	/* Up on y-axis */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.real_up, 2.0F));
	else if (keysym == KEY_DOWN || keysym == KEY_Q)	/* Down on y-axis */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.real_up, 2.0F));
	else if (keysym == KEY_PLUS || keysym == NUMPAD_PLUS)	/* Increase scale */
		apply_object_scale(o, true);
	else if (keysym == KEY_MINUS || keysym == NUMPAD_MINUS)	/* Decrease scale */
		apply_object_scale(o, false);
	else
		return (0);
	cam_recalc(rt);
	render_scene(rt);
	return (0);
}
