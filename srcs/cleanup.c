#include "minirt.h"

/* Clean and exit without error */
int	rt_clean_exit(t_data *rt)
{
	rt_cleanup(rt);
	exit(EXIT_SUCCESS);
}

/* Memory cleanup for .ppm image */
void rt_clean_image(t_ppm image)
{
	t_i i;

	i.y = 0;
	while (i.y < image.height)
	{
		free(image.pixels[i.y]);
		i.y++;
	}
	free(image.pixels);
}

/* Full memory cleanup */
void	rt_cleanup(t_data *rt)
{
	int	i;

	i = 0;
	mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	mlx_destroy_image(rt->mlx_ptr, rt->img->img_ptr);
	while (i < rt->nb_objs)
	{
		if (rt->objs[i]->texture.is_image)
			rt_clean_image(rt->objs[i]->texture.image);
		if (rt->objs[i]->normal.is_image)
			rt_clean_image(rt->objs[i]->normal.image);
		free(rt->objs[i++]);
	}
	free(rt->objs);
	i = 0;
	while (i < rt->nb_lights)
		free(rt->lights[i++]);
	free(rt->lights);
	free(rt->win_name);
	free(rt->img);
	free(rt);
	return ;
}
