/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_rotations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:57:52 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/11/15 15:00:33 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "hooks.h"

/* Track object rotation for allowing texture rotation */
void	save_rot(t_obj *obj, unsigned char axis, bool is_positive)
{
	float	rot_val;

	rot_val = (PI / 16) * (180 / PI);
	if (!is_positive)
		rot_val *= -1;
	if (axis == X_ROT)
		obj->rot.x += rot_val;
	else if (axis == Y_ROT)
		obj->rot.y += rot_val;
	else if (axis == Z_ROT)
		obj->rot.z += rot_val;
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
void	apply_rotation(t_obj *o, unsigned char rot_axis, bool rot_is_positive)
{
	static t_mat4	rot_matrices[6];

	if (!rot_matrices[0].m[0][0])
	{
		rot_matrices[2 * X_ROT + 0] = mat_rot(PI / 16, 'x');
		rot_matrices[2 * X_ROT + 1] = mat_rot(-PI / 16, 'x');
		rot_matrices[2 * Y_ROT + 0] = mat_rot(PI / 16, 'y');
		rot_matrices[2 * Y_ROT + 1] = mat_rot(-PI / 16, 'y');
		rot_matrices[2 * Z_ROT + 0] = mat_rot(PI / 16, 'z');
		rot_matrices[2 * Z_ROT + 1] = mat_rot(-PI / 16, 'z');
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
int	handle_object_rotations(int keysym, t_data *rt)
{
	t_obj	*o;

	o = rt->selected;
	if (keysym == NUMPAD1 || keysym == KEY_1)
		apply_rotation(o, X_ROT, true);
	else if (keysym == NUMPAD2 || keysym == KEY_2)
		apply_rotation(o, X_ROT, false);
	else if (keysym == NUMPAD4 || keysym == KEY_4)
		apply_rotation(o, Y_ROT, true);
	else if (keysym == NUMPAD5 || keysym == KEY_5)
		apply_rotation(o, Y_ROT, false);
	else if (keysym == NUMPAD7 || keysym == KEY_7)
		apply_rotation(o, Z_ROT, true);
	else if (keysym == NUMPAD8 || keysym == KEY_8)
		apply_rotation(o, Z_ROT, false);
	else
		return (0);
	cam_recalc(rt);
	render_scene(rt);
	return (0);
}
