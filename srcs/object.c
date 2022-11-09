#include "minirt.h"


void	obj_move(t_obj *obj)
{
	t_mat4	rot;

	rot = mat_rot_compound(obj->rot.x, obj->rot.y, obj->rot.z);
	obj->fwd = unit_vec3(vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(obj->fwd, T_VEC), rot)));
		obj->right = unit_vec3(cross_vec3(obj->fwd, vec3(0, 1, 0)));
	if (obj->right.x == 0 && obj->right.y == 0 && obj->right.z == 0)
		obj->right = unit_vec3(cross_vec3(obj->fwd, vec3(0, 0, -1)));
	obj->up = unit_vec3(cross_vec3(obj->fwd, obj->right));
}
