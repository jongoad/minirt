#include "minirt.h"
#include "hooks.h"

double	g_fps;


void	print_after_init(t_data *rt)
{
	printf("------- Printing Initialized Scene -------\n\n");

	printf("--- Ambient Light ---\n");
	printf("Intensity: %f\n", rt->ambient.ratio);
	printf("Colour:\n");
	printf("\tr: %d\n", rt->ambient.clr.r);
	printf("\tg: %d\n", rt->ambient.clr.g);
	printf("\tb: %d\n", rt->ambient.clr.b);

	printf("\n--- Camera ---\n");
	printf("Position:\n");
	printf("\tx: %f\n", rt->cam.pos.x);
	printf("\ty: %f\n", rt->cam.pos.y);
	printf("\tz: %f\n", rt->cam.pos.z);
	printf("Orientation:\n");
	printf("\tx: %f\n", rt->cam.aim.x);
	printf("\ty: %f\n", rt->cam.aim.y);
	printf("\tz: %f\n", rt->cam.aim.z);
	printf("FOV: %d\n", rt->cam.fov);

	printf("----- Printing Objects -----\n\n");

	int i = 0;
	while (i < rt->nb_objs)
	{
		printf("--- Object #: %d ---\n", i);
		printf("Object Type: %c\n", rt->objs[i]->type);
		printf("Position:\n");
		printf("\tx: %f\n", rt->objs[i]->center.x);
		printf("\ty: %f\n", rt->objs[i]->center.y);
		printf("\tz: %f\n", rt->objs[i]->center.z);
		printf("Orientation:\n");
		printf("\tx: %f\n", rt->objs[i]->normal.x);
		printf("\ty: %f\n", rt->objs[i]->normal.y);
		printf("\tz: %f\n", rt->objs[i]->normal.z);
		printf("Colour:\n");
		printf("\tr: %d\n", rt->objs[i]->clr.r);
		printf("\tg: %d\n", rt->objs[i]->clr.g);
		printf("\tb: %d\n", rt->objs[i]->clr.b);
		printf("Brightness Ratio: %f\n", rt->objs[i]->ratio);
		printf("Radius: %f\n", rt->objs[i]->radius);
		printf("Height: %f\n", rt->objs[i]->height);
		printf("\n\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err(BAD_ARG_ERR);
	rt = get_data();

	if (!parse(rt, argv[1]))
		return (0);
	print_after_init(rt);

	
	// if (!parse(rt, argv[1]))
	// 	exit_on_err(PARSE_ERR);


	rt_init(rt, argv[1]);

	render_scene(rt, rt->objs[0]);

	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);

	return (0);
}
