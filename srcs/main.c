#include "minirt.h"
#include "hooks.h"



int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err("Error: minirt only accepts a single input\n");
	rt = ft_xalloc(sizeof(t_data));
	rt_init(rt, argv[1]);
	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);
	return (0);
}

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