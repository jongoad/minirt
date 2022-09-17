#include "minirt.h"

int	rt_clean_exit(t_data *cont)
{
	rt_cleanup(cont);
	exit(EXIT_SUCCESS);
}

void	rt_cleanup(t_data *cont)
{
	mlx_destroy_window(cont->mlx_ptr, cont->win_ptr);
	mlx_destroy_image(cont->mlx_ptr, cont->img->img_ptr);
	free(cont->win_name);
	free(cont->img);
	free(cont);
	return ;
}
