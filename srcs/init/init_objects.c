#include "minirt.h"

/* Initialize ambient light object using parsed input data */
void	init_ambient(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	/*FIXME - Replace with non library string to float function */
	rt->ambient.ratio = atof(input[1]);
	init_color(&rt->ambient.clr, input[2]);
} 

/* Initilize camera object using parsed input data */
void	init_camera(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	init_float_triplet(&rt->cam.pos, input[1]);					/* Init camera position */
	init_float_triplet(&rt->cam.forward, input[2]);				/* Init camera orientation */
	init_float_triplet(&rt->cam.aim, input[2]);				/* Init camera orientation */

	rt->cam.fov = ft_atoi(input[3]);							/* Init camera FOV */
}

/* Initialize light object using parsed input data */
void	init_light(t_data *rt, char **input, int obj_nb)
{
	rt->lights[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->lights[obj_nb]->type = T_LIGHT;
	init_float_triplet(&rt->lights[obj_nb]->pos, input[1]);		/* Init light position */
	rt->lights[obj_nb]->ratio = atof(input[2]);					/* Init brightness ratio */
	if (BONUS == 0)
		init_color(&rt->lights[obj_nb]->clr, "255,255,255"); 	/* Init light colour for bonus */
	else
		init_color(&rt->lights[obj_nb]->clr, input[3]); 		/* Init light colour for bonus */
}

/* Initialize plane object using parsed input data */
void	init_plane(t_data *rt, char **input, int obj_nb)	
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->objs[obj_nb]->type = T_PLANE;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);		/* Init plane position */
	rt->objs[obj_nb]->pos_ref = rt->objs[obj_nb]->pos;
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);		/* Init plane orientation */
	init_color(&rt->objs[obj_nb]->clr, input[3]);				/* Init plane color */

	rt->objs[obj_nb]->hit = hit_plane;
}

/* Initialize sphere object using parsed input data */
void	init_sphere(t_data *rt, char **input, int obj_nb)
{
	/*FIXME - Replace with non library string to float function */
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));				/* Allocate object */
	rt->objs[obj_nb]->type = T_SPH;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);		/* Init sphere position */
	rt->objs[obj_nb]->pos_ref = rt->objs[obj_nb]->pos;
	rt->objs[obj_nb]->radius = atof(input[2]) / 2;				/* Init sphere radius */
	init_color(&rt->objs[obj_nb]->clr, input[3]);				/* Init sphere color */

	rt->objs[obj_nb]->hit = hit_sphere;
}

/* Initialize cylinder object using parsed input data */
void	init_cylinder(t_data *rt, char **input, int obj_nb)
{
	t_obj	*o;

	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));			/* Allocate object */
	rt->objs[obj_nb]->type = T_CYL;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);	/* Init cylinder position */
	rt->objs[obj_nb]->pos_ref = rt->objs[obj_nb]->pos;
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);	/* Init cylinder orientation */
	unit_vec3_self(&rt->objs[obj_nb]->fwd);					/* Normalize cylinder orientation */
	rt->objs[obj_nb]->radius = atof(input[3]) / 2;			/* Init cylinder radius */
	rt->objs[obj_nb]->half_height = atof(input[4]);			/* Init cylinder height */
	rt->objs[obj_nb]->half_height /= 2;						/* Only (height / 2) is used */
	init_color(&rt->objs[obj_nb]->clr, input[5]);			/* Init cylinder color */

	// Added by Ismael, to test local_to_world matrices;
	o = rt->objs[obj_nb];
	o->right = unit_vec3(cross_vec3(o->fwd, vec3(0, 1, 0)));
	o->up = unit_vec3(cross_vec3(o->fwd, o->right));
	// o->l_to_w = mat4(vec3_to_vec4(o->up, T_VEC), vec3_to_vec4(o->fwd, T_VEC),
	// 	vec3_to_vec4(o->right, T_VEC), vec3_to_vec4(o->pos, T_POINT));
	o->l_to_w = mat4(vec3_to_vec4(o->right, T_VEC), vec3_to_vec4(o->fwd, T_VEC),
		vec3_to_vec4(o->up, T_VEC), (t_vec4){0, 0, 0, 1});
	
	o->w_to_l = mat_inv(o->l_to_w, 4);

	o->ccap = sub_vec3(
		add_vec3(o->pos, mult_vec3(o->fwd, o->half_height)),
		sub_vec3(o->pos, mult_vec3(o->fwd, o->half_height)));
	o->mag_ccap = dot_vec3(o->ccap, o->ccap);


	// // Rotation
	// double		angle;
	// double		vals[3];
	// t_vec3		axis;

	// angle = acos(dot_vec3(o->fwd, vec3(0, 1, 0)));
	// axis = cross_vec3(o->fwd, vec3(0, 1, 0));
	// vals[0] = cosf(angle);
	// vals[1] = sinf(angle);
	// vals[2] = 1.0 - vals[0];
	
	// o->l_to_w.m[0][0] = vals[0] + (axis.x * axis.x * vals[2]);
	// o->l_to_w.m[0][1] = (axis.x * axis.y * vals[2]) - (axis.z * vals[1]);
	// o->l_to_w.m[0][2] = (axis.x * axis.z * vals[2]) + (axis.y * vals[1]);

	// o->l_to_w.m[1][0] = (axis.y * axis.z * vals[2]) + (axis.z * vals[1]);
	// o->l_to_w.m[1][1] = vals[0] + (axis.y * axis.y * vals[2]);
	// o->l_to_w.m[1][2] = (axis.y * axis.z * vals[2]) - (axis.x * vals[1]);
	
	// o->l_to_w.m[2][0] = (axis.z * axis.x * vals[2]) - (axis.y * vals[1]);
	// o->l_to_w.m[2][1] = (axis.z * axis.y * vals[2]) + (axis.x * vals[1]);
	// o->l_to_w.m[2][2] = vals[0] + (axis.z * axis.z * vals[2]);
	
	// // Translation
	// o->l_to_w.m[0][3] = o->pos.x;
	// o->l_to_w.m[1][3] = o->pos.y;
	// o->l_to_w.m[2][3] = o->pos.z;
	// o->l_to_w.m[3][3] = 0;


	o->w_to_l = mat_inv(o->l_to_w, 4);


	rt->objs[obj_nb]->hit = hit_cylinder;
	// rt->objs[obj_nb]->hit = hit_cone;
}