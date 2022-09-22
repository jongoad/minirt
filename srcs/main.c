#include "minirt.h"
#include "hooks.h"

double	g_fps;

bool	hit_sphere(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec, float t_min);

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

	generate_sphere_shaded(rt, rt->objs[0]);

	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);

	return (0);
}
