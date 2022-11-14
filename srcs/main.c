#include "minirt.h"
#include "hooks.h"

double	g_fps;

/* Main data structure singleton fetch function */
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

	if (argc != 2)						/* Check for invalid command line input */
		exit_on_err(BAD_ARG_ERR);
	rt = get_data();					/* Initialize main data struct */
	if (!parse(rt, argv[1]))			/* Run parsing */
		return (0);
	rt_init(rt, argv[1]);				/* Initialize renderer & scene after succesful parse */
	set_hooks(rt);						/* Set up hooks for MLX */
	cam_init(rt);
	render_scene(rt);					/* Preliminary render before entering main loop */
	display_default(rt);				/* Push rendered image to window */
	mlx_loop(rt->mlx_ptr);				/* Enter into main loop */
	return (0);
}