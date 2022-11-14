#include "minirt.h"

/* Initialize plane object using parsed input data */
void	init_plane(t_data *rt, char **input, int obj_nb)	
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_PLANE;								/* Set object type*/
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);			/* Set plane position */
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);			/* Set plane orientation */
	unit_vec3_self(&rt->objs[obj_nb]->fwd);							/* Normalize plane orientation */
	init_color(&rt->objs[obj_nb]->clr, input[3]);					/* Set plane color */
	rt->objs[obj_nb]->hit = hit_plane;
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[4])											/* Set bonus attributes */
		init_obj_bonus(rt->objs[obj_nb], &input[4]);
}

/* Initialize sphere object using parsed input data */
void	init_sphere(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_SPH;									/* Set object type */
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);			/* Set sphere position */
	rt->objs[obj_nb]->radius = ft_atof(input[2]) / 2;				/* Set sphere radius */
	rt->objs[obj_nb]->ref_radius = rt->objs[obj_nb]->radius;
	init_color(&rt->objs[obj_nb]->clr, input[3]);					/* Set sphere color */
	rt->objs[obj_nb]->hit = hit_sphere;
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[4])											/* Set bonus attributes */
		init_obj_bonus(rt->objs[obj_nb], &input[4]);
}

/* Initialize cylinder object using parsed input data */
void	init_cylinder(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_CYL;									/* Set object type */
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);			/* Set cylinder position */
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);			/* Set cylinder orientation */
	unit_vec3_self(&rt->objs[obj_nb]->fwd);							/* Normalize cylinder orientation */
	rt->objs[obj_nb]->radius = ft_atof(input[3]) / 2;				/* Set cylinder radius */
	rt->objs[obj_nb]->half_height = ft_atof(input[4]) / 2;			/* Set cylinder height, only (height / 2) is used */
	rt->objs[obj_nb]->ref_radius = 	rt->objs[obj_nb]->radius;
	rt->objs[obj_nb]->ref_half_height = rt->objs[obj_nb]->half_height;
	init_color(&rt->objs[obj_nb]->clr, input[5]);					/* Set cylinder color */
	rt->objs[obj_nb]->hit = hit_cylinder;
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[6])											/* Set bonus attributes */
		init_obj_bonus(rt->objs[obj_nb], &input[6]);
}

/* Initialize cone object using parsed data */
void	init_cone(t_data *rt, char **input, int obj_nb)
{
	double	half_tan;

	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_CONE;								/* Set object type*/
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);			/* Set cone position */
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);			/* Set cone orientation */
	unit_vec3_self(&rt->objs[obj_nb]->fwd);							/* Normalize cone orientation */
	half_tan = tanf(deg_to_rad(ft_atof(input[3]))) / 2.0F;
	rt->objs[obj_nb]->half_height = ft_atof(input[4]) / 2;			/* Set cone height, only (height / 2) is used */
	rt->objs[obj_nb]->radius = tanf(rt->objs[obj_nb]->angle_ofs)
		* rt->objs[obj_nb]->half_height;							/* Set cone height, only (height / 2) is used */
	rt->objs[obj_nb]->angle_ofs = 1 + half_tan * half_tan;			/* Set cone angle */
	rt->objs[obj_nb]->ref_angle = ft_atof(input[3]);
	rt->objs[obj_nb]->ref_half_height = rt->objs[obj_nb]->half_height;
	init_color(&rt->objs[obj_nb]->clr, input[5]);					/* Set cone color */
	rt->objs[obj_nb]->hit = hit_cone;
	rt->objs[obj_nb]->rot = vec3(0,0,0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[6])											/* Set bonus attributes */
		init_obj_bonus(rt->objs[obj_nb], &input[6]);
}
