#include "minirt.h"

void	rt_init(t_data *rt, char *file)
{
	t_img	*img;

	rt->mlx_ptr = mlx_init();
	if (!rt->mlx_ptr)
		exit_on_err("mlx: mlx_init() error \n");
	rt->win_name = ft_strjoin_free(ft_get_last_token(file, '/'), " - minirt");
	rt->win_ptr = mlx_new_window(
			rt->mlx_ptr, IMG_W, IMG_H, rt->win_name);
	if (!rt->win_ptr)
		exit_on_err("mlx: mlx_new_window() error \n");
	rt->img = ft_xalloc(sizeof(t_img));
	img = rt->img;
	img->width = IMG_W;
	img->height = IMG_H;
	img->img_ptr = mlx_new_image(rt->mlx_ptr, img->width, img->height);
	img->data_addr = mlx_get_data_addr(
			img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	return ;
}
