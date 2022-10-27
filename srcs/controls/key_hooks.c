#include "minirt.h"
#include "hooks.h"

static int	handle_object_translations(int keysym, t_data *rt);
static int	handle_object_rotations(int keysym, t_data *rt);

int	handle_key_release_hook(int keysym, t_data *rt)
{
	if (keysym == KEY_ESC)
		rt_clean_exit(rt);
	else if (keysym == KEY_L)
	{
		rt->apply_light_halos = !(rt->apply_light_halos);
		render_scene(rt);
	}
	else if (keysym == KEY_F1)
		print_usage();
	else
		return (0);
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
		render_scene(rt);
	}
	else if (rt->selected_obj_id != NO_HIT)
	{
		handle_object_translations(keysym, rt);
		handle_object_rotations(keysym, rt);
	}
	return (0);
}

static int	handle_object_translations(int keysym, t_data *rt)
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
	render_scene(rt);
	return (0);
}

static void	apply_rotation(t_obj *o, unsigned char rot_axis, bool rot_is_positive)
{
	static t_mat4	rot_matrices[6];

	if (!rot_matrices[0].m[0][0])	// If unitialized
	{
		rot_matrices[2 * X_ROT + 0] = mat_rot(PI/16, 'x');
		rot_matrices[2 * X_ROT + 1] = mat_rot(-PI/16, 'x');
		rot_matrices[2 * Y_ROT + 0] = mat_rot(PI/16, 'y');
		rot_matrices[2 * Y_ROT + 1] = mat_rot(-PI/16, 'y');
		rot_matrices[2 * Z_ROT + 0] = mat_rot(PI/16, 'z');
		rot_matrices[2 * Z_ROT + 1] = mat_rot(-PI/16, 'z');
	}
	if (rot_axis > Z_ROT)
		return ;
	o->fwd = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(o->fwd, T_POINT), rot_matrices[2 * rot_axis + rot_is_positive]));
	o->right = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(o->right, T_POINT), rot_matrices[2 * rot_axis + rot_is_positive]));
	o->up = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(o->up, T_POINT), rot_matrices[2 * rot_axis + rot_is_positive]));
}

static int	handle_object_rotations(int keysym, t_data *rt)
{
	t_obj	*o;
	
	o = rt->objs[rt->selected_obj_id];
	if (keysym == NUMPAD1)		/* Rotate clockwise around x axis */
		apply_rotation(o, X_ROT, true);
	else if (keysym == NUMPAD2)		/* Rotate counter-clockwise x axis */
		apply_rotation(o, X_ROT, false);
	else if (keysym == NUMPAD4)		/* Rotate clockwise around y axis */
		apply_rotation(o, Y_ROT, true);
	else if (keysym == NUMPAD5)		/* Rotate counter-clockwise y axis */
		apply_rotation(o, Y_ROT, false);
	else if (keysym == NUMPAD7)		/* Rotate clockwise around z axis */
		apply_rotation(o, Z_ROT, true);
	else if (keysym == NUMPAD8)		/* Rotate counter-clockwise z axis */
		apply_rotation(o, Z_ROT, false);
	else
		return (0);
	cam_recalc(rt);
	render_scene(rt);
	return (0);
}
