#include "minirt.h"


void	obj_calc_mat(t_obj *obj)
{
	obj->right = unit_vec3(cross_vec3(obj->fwd, vec3(0, 1, 0)));
	obj->up = unit_vec3(cross_vec3(obj->fwd, obj->right));
	obj->l_to_w = mat4(vec3_to_vec4(obj->right, T_VEC), vec3_to_vec4(obj->up, T_VEC),
		vec3_to_vec4(obj->fwd, T_VEC), vec3_to_vec4(obj->pos, T_POINT));
	obj->w_to_l = mat_inv(obj->l_to_w, 4);
}


void	obj_move(t_obj *obj)
{
	t_mat4	rot;

	rot = mat_rot_compound(obj->rot.x, obj->rot.y, obj->rot.z);
	obj->fwd = unit_vec3(vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(obj->fwd, T_VEC), rot)));
	obj_calc_mat(obj);
}