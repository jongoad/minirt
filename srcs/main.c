#include "minirt.h"
#include "hooks.h"

double	g_fps;

int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err("Error: minirt only accepts a single input\n");
	rt = get_data();
	rt_init(rt, argv[1]);
	// hello_world(rt);
	// generate_background(rt);
	// generate_sphere_simple(rt);

	t_vec3		sp_center = vec3(0,0,-1);
	generate_sphere_shaded(rt, &sp_center);

	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);

	return (0);
}
