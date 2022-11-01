#include "minirt.h"

/* Memory safe allocation */
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

/* Error messaging & exit */
void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit(EXIT_FAILURE);
}

/* Linear interpolation */
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

void	fill_pixel(t_img *img, int x, int y, t_color color)
{
	*(int *)(char *)(img->data_addr + x * img->bpp / 8 + y * img->line_len) \
		= color_to_int(color);
}

void	print_usage(void)
{
	printf("%s\n*** Object Rotations ***\n%s", BASH_CYAN, BASH_RESET);
	printf("x axis:   NUMPAD1 // NUMPAD2\n");
	printf("y axis:   NUMPAD4 // NUMPAD5\n");
	printf("z axis:   NUMPAD7 // NUMPAD8\n");
	printf("Toggle All:  'R'\n");
	printf("%s\n*** Object Translations ***\n%s", BASH_CYAN, BASH_RESET);
	printf("x axis:   KEY_LEFT / 'A' 		// KEY_RIGHT / 'D'\n");
	printf("y axis:   KEY_UP / KEY_Z 		// KEY_DOWN / KEY_X\n");
	printf("z axis:   MOUSE_WHEEL_UP / 'W'  // MOUSE_WHEEL_UP / 'D' \n");
	printf("%s\n*** Object Scale ***\n%s", BASH_CYAN, BASH_RESET);
	printf("scale:         '+' // '-' \n");
	printf("%s\n*** Fun stuff ***\n%s", BASH_CYAN, BASH_RESET);
	printf("Toggle Light Halos:  'L'\n");
	printf("Print usage:      			   KEY_F1\n");
	printf("Print selected obj info:       SPACEBAR\n");
}
