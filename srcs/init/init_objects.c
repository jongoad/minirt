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
	rt->objs[obj_nb]->height = atof(input[4]);				/* Init cylinder height */
	init_color(&rt->objs[obj_nb]->clr, input[5]);			/* Init cylinder color */

	// Added by Ismael, to test local_to_world matrices;
	o = rt->objs[obj_nb];
	o->right = unit_vec3(cross_vec3(o->fwd, vec3(0, 1, 0)));
	o->up = unit_vec3(cross_vec3(o->fwd, o->right));
	o->l_to_w = mat4(vec3_to_vec4(o->right, T_VEC), vec3_to_vec4(o->up, T_VEC),
		vec3_to_vec4(o->fwd, T_VEC), vec3_to_vec4(o->pos, T_POINT));
	
	o->w_to_l = mat_inv(o->l_to_w, 4);

	o->ccap = mult_vec3(o->fwd, o->height);
	o->mag_ccap = dot_vec3(o->ccap, o->ccap);

	rt->objs[obj_nb]->hit = hit_cylinder;
}