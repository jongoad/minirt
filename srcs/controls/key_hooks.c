#include "minirt.h"
#include "hooks.h"

static int	handle_key_press_objects(int keysym, t_data *rt);

int	handle_key_release_hook(int keysym, t_data *rt)
{
	if (keysym == KEY_ESC)
		rt_clean_exit(rt);
	if (keysym == KEY_L)
	{
		rt->apply_light_halos = !(rt->apply_light_halos);
		render_scene(rt, rt->objs[0]);
	}
	return (0);
}

int	handle_key_press_hook(int keysym, t_data *rt)
{
	if (rt->cam.is_move)
	{
		if (keysym == KEY_W)			/* Move camera forwards */
			rt->cam.pos = add_vec3(rt->cam.pos, mult_vec3(rt->cam.forward, CAM_TRANS_RATE));
		if (keysym == KEY_S)			/* Move camera backwards */
			rt->cam.pos = sub_vec3(rt->cam.pos, mult_vec3(rt->cam.forward, CAM_TRANS_RATE));
		if (keysym == KEY_A)			/* Move camera left */
			rt->cam.pos = sub_vec3(rt->cam.pos, mult_vec3(rt->cam.right, CAM_TRANS_RATE));
		if (keysym == KEY_D)			/* Move camera right */
			rt->cam.pos = add_vec3(rt->cam.pos, mult_vec3(rt->cam.right, CAM_TRANS_RATE));
		if (keysym == KEY_Q)			/* Move camera down */
			rt->cam.pos = sub_vec3(rt->cam.pos, mult_vec3(rt->cam.up, CAM_TRANS_RATE));
		if (keysym == KEY_E)			/* Move camera up */
			rt->cam.pos = add_vec3(rt->cam.pos, mult_vec3(rt->cam.up, CAM_TRANS_RATE));
		cam_recalc(rt);
		render_scene(rt, rt->objs[0]);
	}
	else if (rt->selected_obj_id != NO_HIT)
		handle_key_press_objects(keysym, rt);
	return (0);
}

static int	handle_key_press_objects(int keysym, t_data *rt)
{
	t_obj	*o;

	o = rt->objs[rt->selected_obj_id];
	if (keysym == KEY_S)		/* Move obj closer */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.forward, 2.0F));
	else if (keysym == KEY_W)		/* Move obj further */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.forward, 2.0F));
	else if (keysym == KEY_RIGHT || keysym == KEY_D)		/* Move obj right */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.right, 2.0F));
	else if (keysym == KEY_LEFT || keysym == KEY_A)		/* Move obj left */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.right, 2.0F));
	else if (keysym == KEY_UP || keysym == KEY_E)		/* Move obj up */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.up, 2.0F));
	else if (keysym == KEY_DOWN || keysym == KEY_Q)		/* Move obj down */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.up, 2.0F));
	else if (keysym == KEY_PLUS || keysym == NUMPAD_PLUS)
		o->radius += 0.01;
	else if (keysym == KEY_MINUS || keysym == NUMPAD_MINUS)
		o->radius -= 0.01;
	else
		return (0);
	cam_recalc(rt);
	render_scene(rt, rt->objs[0]);
	return (0);
}
