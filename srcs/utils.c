#include "minirt.h"

void	*ft_xalloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	if (!mem_space)
	{
		write(STDERR_FILENO, "Malloc Error\n", 13);
		exit (EXIT_FAILURE);
	}
	return (mem_space);
}

void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit(EXIT_FAILURE);
}

/**
 * @param start value 
 * @param ratio Between 0.0 and 1.0
 * @return int 	interpolated color
 */
int	lerp_color(int start, float ratio)
{
	int	color;
	
	if (ratio <= 0.0F || ratio > 1.0F)
		return 0;
	else if (ratio == 1.0F)
		return (start);
	color = (int)((start >> 16 & 0xFF) * ratio) << 16;
	color |= (int)((start >> 8 & 0xFF) * ratio) << 8;
	color |= (int)((start & 0xFF) * ratio);
	return (color);
}

double	lerp(double start, double end, double curr)
{
	if (curr == start || end == start)
		return (0.0F);
	else if (curr == end)
		return (1.0F);
	return ((curr - start) / (end - start));
}

void	draw_background(t_img *img, int color)
{
	ft_memset(img->data_addr, color, img->line_len * img->height);
}

void	fill_pixel(t_img *img, int x, int y, int color)
{
	// char	*cast_ptr;

	*(int *)(char *)(img->data_addr + x * img->bpp / 8 + y * img->line_len) = color;
	// cast_ptr = (char *)(img->data_addr + x * img->bpp / 8 + y * img->line_len);
	// *(int *)cast_ptr = color;
}
