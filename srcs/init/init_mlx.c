#include "minirt.h"

/* Initialize mlx window */
void	rt_init_mlx(t_data *rt, char *filename)
{
	rt->mlx_ptr = mlx_init();
	if (!rt->mlx_ptr)
		exit_on_err("mlx: mlx_init() error \n");
	rt->win_name = ft_strjoin_free(
			ft_get_last_token(filename, '/'), " - minirt");					/* Get custom window name based on loaded file */
	rt->win_ptr = mlx_new_window(
			rt->mlx_ptr, IMG_W, IMG_H, rt->win_name);						/* Create new mlx window */
	if (!rt->win_ptr)
		exit_on_err("mlx: mlx_new_window() error \n");
}

/* Initialize mlx image */
void	rt_init_img(t_data *rt)
{
	t_img	*img;
	
	rt->img = ft_xalloc(sizeof(t_img));
	img = rt->img;
	img->width = IMG_W;														/* Set window dimensions*/
	img->height = IMG_H;
	img->img_ptr = mlx_new_image(rt->mlx_ptr, img->width, img->height);		/* Get mlx image pointer */
	img->data_addr = mlx_get_data_addr(
			img->img_ptr, &img->bpp, &img->line_len, &img->endian);			/* Get mlx image data */
}
