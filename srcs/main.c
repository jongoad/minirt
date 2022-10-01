#include "minirt.h"
#include "hooks.h"

double	g_fps;


int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err(BAD_ARG_ERR);
	rt = get_data();

	
	// if (!parse(rt, argv[1]))
	// 	exit_on_err(PARSE_ERR);


	rt_init(rt, argv[1]);
	// hello_world(rt);
	// generate_background(rt);
	// generate_sphere_simple(rt);

	generate_sphere_shaded(rt, rt->objs[0]);

	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);

	return (0);
}
