#include "minirt.h"

int	rt_clean_exit(t_data *rt)
{
	rt_cleanup(rt);
	exit(EXIT_SUCCESS);
}

void	rt_cleanup(t_data *rt)
{
	mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	mlx_destroy_image(rt->mlx_ptr, rt->img->img_ptr);
	free(rt->win_name);
	free(rt->img);
	free(rt);

	//FIXME: from rt_one_weekend
	free(get_sphere());
	
	return ;
}
