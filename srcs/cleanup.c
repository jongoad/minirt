#include "minirt.h"

int	rt_clean_exit(t_data *rt)
{
	rt_cleanup(rt);
	exit(EXIT_SUCCESS);
}

void	rt_cleanup(t_data *rt)
{
	int	i;


	mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	mlx_destroy_image(rt->mlx_ptr, rt->img->img_ptr);
	
	i = 0;
	while (i < rt->nb_objs)
		free(rt->objs[i++]);
	free(rt->objs);
	
	free(rt->lights);
	
	free(rt->win_name);
	free(rt->img);
	free(rt);

	return ;
}
