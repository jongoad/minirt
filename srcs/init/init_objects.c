#include "minirt.h"

/* Initialize plane object using parsed input data */
void	init_plane(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_PLANE;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);
	unit_vec3_self(&rt->objs[obj_nb]->fwd);
	init_color(&rt->objs[obj_nb]->clr, input[3]);
	rt->objs[obj_nb]->hit = hit_plane;
	rt->objs[obj_nb]->rot = vec3(0, 0, 0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[4])
		init_obj_bonus(rt->objs[obj_nb], &input[4]);
}

/* Initialize sphere object using parsed input data */
void	init_sphere(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_SPH;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);
	rt->objs[obj_nb]->radius = ft_atof(input[2]) / 2;
	rt->objs[obj_nb]->ref_radius = rt->objs[obj_nb]->radius;
	init_color(&rt->objs[obj_nb]->clr, input[3]);
	rt->objs[obj_nb]->hit = hit_sphere;
	rt->objs[obj_nb]->rot = vec3(0, 0, 0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[4])
		init_obj_bonus(rt->objs[obj_nb], &input[4]);
}

/* Initialize cylinder object using parsed input data */
void	init_cylinder(t_data *rt, char **input, int obj_nb)
{
	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_CYL;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);
	unit_vec3_self(&rt->objs[obj_nb]->fwd);
	rt->objs[obj_nb]->radius = ft_atof(input[3]) / 2;
	rt->objs[obj_nb]->half_height = ft_atof(input[4]) / 2;
	rt->objs[obj_nb]->ref_radius = rt->objs[obj_nb]->radius;
	rt->objs[obj_nb]->ref_half_height = rt->objs[obj_nb]->half_height;
	init_color(&rt->objs[obj_nb]->clr, input[5]);
	rt->objs[obj_nb]->hit = hit_cylinder;
	rt->objs[obj_nb]->rot = vec3(0, 0, 0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[6])
		init_obj_bonus(rt->objs[obj_nb], &input[6]);
}

/* Initialize cone object using parsed data */
void	init_cone(t_data *rt, char **input, int obj_nb)
{
	double	half_tan;

	rt->objs[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->objs[obj_nb]->type = T_CONE;
	init_float_triplet(&rt->objs[obj_nb]->pos, input[1]);
	init_float_triplet(&rt->objs[obj_nb]->fwd, input[2]);
	unit_vec3_self(&rt->objs[obj_nb]->fwd);
	rt->objs[obj_nb]->angle = deg_to_rad(ft_atof(input[3]));
	half_tan = tanf(rt->objs[obj_nb]->angle);
	rt->objs[obj_nb]->half_height = ft_atof(input[4]) / 2;
	rt->objs[obj_nb]->radius = tanf(rt->objs[obj_nb]->angle)
		* rt->objs[obj_nb]->half_height;
	rt->objs[obj_nb]->angle_ofs = 1 + half_tan * half_tan;
	rt->objs[obj_nb]->ref_half_height = rt->objs[obj_nb]->half_height;
	init_color(&rt->objs[obj_nb]->clr, input[5]);
	rt->objs[obj_nb]->hit = hit_cone;
	rt->objs[obj_nb]->rot = vec3(0, 0, 0);
	rt->objs[obj_nb]->scale = 1.0f;
	rt->objs[obj_nb]->shininess = SHININESS;
	rt->objs[obj_nb]->texture.is_image = false;
	rt->objs[obj_nb]->texture.is_checkers = false;
	rt->objs[obj_nb]->normal.is_image = false;
	if (BONUS && input[6])
		init_obj_bonus(rt->objs[obj_nb], &input[6]);
}
