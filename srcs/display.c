#include "minirt.h"

int	display_default(t_data *rt)
{
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
	return (0);
}

int	display_img(t_data *rt, t_img *img)
{
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, img->img_ptr, 0, 0);
	return (0);
}
