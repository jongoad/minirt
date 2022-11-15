#include "minirt.h"

/* Push mlx image to window to be displayed */
int	display_default(t_data *rt)
{
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
	return (0);
}

/* Write pixel data to mlx image */
void	fill_pixel(t_img *img, int x, int y, t_color color)
{
	*(int *)(char *)(img->data_addr + x * img->bpp / 8 + y * img->line_len) \
		= color_to_int(color);
}
