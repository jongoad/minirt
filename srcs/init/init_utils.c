#include "minirt.h"

/* Split a colour input into components */
void	init_color(t_color *clr, char *input)
{
	char **split;

	split = ft_split(input, ',');
	clr->r = ft_atoi(split[0]);
	clr->g = ft_atoi(split[1]);
	clr->b = ft_atoi(split[2]);
	clr->weight = 1;
	ft_free_split(split);
}

/* Initialize a vec3 from parsed input data */
void	init_float_triplet(t_vec3 *vec, char *input)
{
	/* FIXME - Replace string to float with non library version */
	char **split;

	split = ft_split(input, ',');
	vec->x = atof(split[0]);
	vec->y = atof(split[1]);
	vec->z = atof(split[2]);
}

/* Count objects for allocation and final parse step */
void	count_objects(t_data *rt)
{
	int res;
	int	i;

	i = 0;
	res = 0;
	rt->nb_objs = 0;
	rt->nb_lights = 0;
	while (rt->parse.scene[i])
	{
		res = check_tok(rt->parse.scene[i][0], rt->parse.tok);
		if (res > 2)
			rt->nb_objs++;
		else if (res == 2)
			rt->nb_lights++;
		i++;
	}
}

/* Initilialize function pointer array for object init */
void	init_parse_fct_ptrs(t_data *rt)
{
	rt->parse.f2[0] = init_ambient;
	rt->parse.f2[1] = init_camera;
	rt->parse.f2[2] = init_light;
	rt->parse.f2[3] = init_plane;
	rt->parse.f2[4] = init_sphere;
	rt->parse.f2[5] = init_cylinder;
}