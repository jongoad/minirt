#include "minirt.h"



int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err("Error: FdF only accepts one input\n");
	rt = ft_xalloc(sizeof(t_data));
	fdf_parse(rt, argv[1]);
	fdf_init(rt, argv[1]);
	center_map(rt);
	display_map(rt);
	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);
	return (0);}

// int	main(int argc, char **argv)
// {
// 	if (!parse())
// 		exit();
// 	init_scene();
// 	init_mlx();
// 	loop();

// 	cleanup();
// 	exit();
// }

void	loop()
{
	//Run mlx loop
}

void	init_mlx()
{
	//Set up mlx windows and images
	//Setup hooks
}