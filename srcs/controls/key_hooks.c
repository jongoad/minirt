#include "minirt.h"
#include "hooks.h"

static int	handle_object_translations(int keysym, t_data *rt);
static int	handle_object_rotations(int keysym, t_data *rt);

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
			rt->cam.pos = sub_vec3(rt->cam.pos, mult_vec3(rt->cam.real_up, CAM_TRANS_RATE));
		if (keysym == KEY_E)			/* Move camera up */
			rt->cam.pos = add_vec3(rt->cam.pos, mult_vec3(rt->cam.real_up, CAM_TRANS_RATE));
		cam_recalc(rt);
		render_scene(rt);
	}
	else if (rt->selected != NULL)
	{
		if (keysym == KEY_SPACE)
			print_obj_data(rt->selected);
		handle_object_translations(keysym, rt);
		handle_object_rotations(keysym, rt);
	}
	return (0);
}
void	apply_object_scale(t_obj *o, bool is_positive)
{
	/* Apply change to scale value*/
	if (is_positive)
		o->scale *= 1.1;
	else
	{
		o->scale /= 1.1;
		if (o->scale > 0.1)
			o->scale = 0.1;
	}
	if (o->type == T_SPH || o->type == T_CYL)				/* If sphere or cylinder adjust radius */
		o->radius = o->ref_radius * o->scale;
	if (o->type == T_CYL || o->type == T_CONE)				/* If cylinder or cone adjust height */
		o->half_height = o->ref_half_height * o->scale;
	if (o->type == T_CONE)									/* If cone set new radius based on height */
		o->radius = tanf(o->angle) * o->half_height;
}

/* Object translation keyhook handling */
static int	handle_object_translations(int keysym, t_data *rt)
{
	t_obj	*o;

	o = rt->selected;
	if (keysym == KEY_S)											/* Move obj closer */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.forward, 2.0F));
	else if (keysym == KEY_W)										/* Move obj further */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.forward, 2.0F));
	else if (keysym == KEY_RIGHT || keysym == KEY_D)				/* Move obj right */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.right, 2.0F));
	else if (keysym == KEY_LEFT || keysym == KEY_A)					/* Move obj left */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.right, 2.0F));
	else if (keysym == KEY_UP || keysym == KEY_E)					/* Move obj up */
		add_vec3_self(&o->pos, mult_vec3(rt->cam.real_up, 2.0F));
	else if (keysym == KEY_DOWN || keysym == KEY_Q)					/* Move obj down */
		sub_vec3_self(&o->pos, mult_vec3(rt->cam.real_up, 2.0F));
	else if (keysym == KEY_PLUS || keysym == NUMPAD_PLUS)			/* Increase obj scale */
		apply_object_scale(o, true);
	else if (keysym == KEY_MINUS || keysym == NUMPAD_MINUS)			/* Decrease obj scale */
		apply_object_scale(o, false);
	else
		return (0);
	cam_recalc(rt);
	render_scene(rt);
	return (0);
}

/* Track object rotation for allowing texture rotation */
void	save_rot(t_obj *obj, unsigned char axis, bool is_positive)
{
	float rot_val;

	rot_val = (PI/16) * (180/PI);
	if (!is_positive)
		rot_val *= -1; 
	if (axis == X_ROT)
		obj->rot.x += rot_val;
	else if (axis == Y_ROT)
		obj->rot.y += rot_val;
	else if (axis == Z_ROT)
		obj->rot.z += rot_val;

	/* Handle overotation */
	if (obj->rot.x < 0)
		obj->rot.x = (int)obj->rot.x % 360;
	else if (obj->rot.x > 0)
		obj->rot.x = (int)obj->rot.x % -360;
	if (obj->rot.y < 0)
		obj->rot.y = (int)obj->rot.y % 360;
	else if (obj->rot.y > 0)
		obj->rot.y = (int)obj->rot.y % -360;
	if (obj->rot.z < 0)
		obj->rot.z = (int)obj->rot.z % 360;
	else if (obj->rot.z > 0)
		obj->rot.z = (int)obj->rot.z % -360;
}

/* Apply rotation to an object using keyboard controls*/
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
	save_rot(o, rot_axis, rot_is_positive);
	o->fwd = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(o->fwd, T_POINT),
		rot_matrices[2 * rot_axis + rot_is_positive]));
	o->right = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(o->right, T_POINT),
		rot_matrices[2 * rot_axis + rot_is_positive]));
	o->up = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(o->up, T_POINT),
		rot_matrices[2 * rot_axis + rot_is_positive]));
}

/* Object rotation keyhook handling */
static int	handle_object_rotations(int keysym, t_data *rt)
{
	t_obj	*o;
	
	o = rt->selected;
	if (keysym == NUMPAD1 || keysym == KEY_1)			/* Rotate clockwise around x axis */
		apply_rotation(o, X_ROT, true);
	else if (keysym == NUMPAD2 || keysym == KEY_2)		/* Rotate counter-clockwise x axis */
		apply_rotation(o, X_ROT, false);
	else if (keysym == NUMPAD4 || keysym == KEY_4)		/* Rotate clockwise around y axis */
		apply_rotation(o, Y_ROT, true);
	else if (keysym == NUMPAD5 || keysym == KEY_5)		/* Rotate counter-clockwise y axis */
		apply_rotation(o, Y_ROT, false);
	else if (keysym == NUMPAD7 || keysym == KEY_7)		/* Rotate clockwise around z axis */
		apply_rotation(o, Z_ROT, true);
	else if (keysym == NUMPAD8 || keysym == KEY_8)		/* Rotate counter-clockwise z axis */
		apply_rotation(o, Z_ROT, false);
	else
		return (0);
	cam_recalc(rt);
	render_scene(rt);
	return (0);
}
