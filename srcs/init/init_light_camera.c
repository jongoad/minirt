#include "minirt.h"

/* Initialize ambient light object using parsed input data */
void	init_ambient(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	rt->ambient.ratio = ft_atof(input[1]);
	init_color(&rt->ambient.clr, input[2]);
	rt->ambient.scene_ambient
		= mult_vec3(color_to_vec3(rt->ambient.clr),
			rt->ambient.ratio / 255);
}

/* Initilize camera object using parsed input data */
void	init_camera(t_data *rt, char **input, int obj_nb)
{
	(void)obj_nb;
	init_float_triplet(&rt->cam.pos, input[1]);
	init_float_triplet(&rt->cam.forward, input[2]);
	rt->cam.fov = ft_atoi(input[3]);
}

/* Initialize light object using parsed input data */
void	init_light(t_data *rt, char **input, int obj_nb)
{
	rt->lights[obj_nb] = ft_xalloc(sizeof(t_obj));
	rt->lights[obj_nb]->type = T_LIGHT;
	init_float_triplet(&rt->lights[obj_nb]->pos, input[1]);
	rt->lights[obj_nb]->ratio = ft_atof(input[2]);
	if (BONUS && input[3])
		init_color(&rt->lights[obj_nb]->clr, input[3]);
	else
		init_color(&rt->lights[obj_nb]->clr, "255,255,255");
	rt->lights[obj_nb]->clr = mult_color(
			rt->lights[obj_nb]->clr, rt->lights[obj_nb]->ratio);
}
