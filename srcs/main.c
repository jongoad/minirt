#include "minirt.h"
#include "hooks.h"

double	g_fps;

bool	hit_sphere(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec, float t_min);

t_obj	*get_sphere( )
{
	static t_obj	*sp;

	if (!sp) {
		t_vec3	center = { .x = 0, .y = 0, .z = -1.0F };
		sp = ft_xalloc(sizeof(t_obj));
		sp->radius = 0.05F;
		sp->center = center;
		sp->color = lerp_color(CYAN, 0.2);
		sp->type = 's';
		sp->hit = hit_sphere;
	}
	return (sp);
}

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

	t_obj		*sp = get_sphere();
	
	generate_sphere_shaded(rt, sp);

	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);

	return (0);
}
