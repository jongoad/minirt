#include "minirt.h"



int	main(int argc, char **argv)
{
	if (!parse())
		exit();
	init_scene();
	init_mlx();
	loop();

	cleanup();
	exit();
}

void	loop()
{
	//Run mlx loop
}

void	init_mlx()
{
	//Set up mlx windows and images
	//Setup hooks
}