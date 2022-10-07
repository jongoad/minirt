#include "minirt.h"
#include "hooks.h"

double	g_fps;




int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err(BAD_ARG_ERR);
	rt = get_data();

	if (!parse(rt, argv[1]))
		return (0);
	print_scene_after_init(rt);



	// rt_init(rt, argv[1]);

	// render_scene(rt, rt->objs[0]);

	// set_hooks(rt);
	// mlx_loop(rt->mlx_ptr);

	return (0);
}
