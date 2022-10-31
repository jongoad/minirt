#include "minirt.h"
#include "hooks.h"

double	g_fps;

t_data	*get_data(void)
{
	static t_data *data;

	if (!data)
		data = ft_xalloc(sizeof(t_data));
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*rt;

	t_vec3	orig	= {1, 1, 1, 0};
	t_vec3	normal	= {0, 1, 0, 0};

	unit_vec3_self(&orig);
	printf("original vector: ");
	print_vec3(orig);
	printf("\nnormal vector: ");
	print_vec3(normal);
	printf("\n");

	print_vec3(reflect_ray(orig, normal));
	printf("\n");

	/* Check for invalid command line input */
	if (argc != 2)
		exit_on_err(BAD_ARG_ERR);
	rt = get_data();

	/* Run parsing */
	if (!parse(rt, argv[1]))
		return (0);

	/* Initialize renderer after succesful parse */
	rt_init(rt, argv[1]);
	
	set_hooks(rt);
	cam_init(rt);
	// print_scene_after_init(rt);

	cam_recalc(rt);

	/* Preliminary render before entering main loop */
	render_scene(rt);

	/* Enter into main loop */
	mlx_loop(rt->mlx_ptr);

	return (0);
}
