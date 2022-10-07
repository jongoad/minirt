#include "minirt.h"

#define RED "\033[1;31m"
#define CLEAR "\033[0m"


void	print_scene_after_init(t_data *rt)
{
	printf(RED"------- Printing Initialized Scene -------\n\n"CLEAR);

	printf(RED"--- Ambient Light ---\n"CLEAR);
	printf("Intensity: %f\n", rt->ambient.ratio);
	printf("Colour:\n");
	printf("\tr: %d\n", rt->ambient.clr.r);
	printf("\tg: %d\n", rt->ambient.clr.g);
	printf("\tb: %d\n", rt->ambient.clr.b);

	printf(RED"\n--- Camera ---\n"CLEAR);
	printf("Position:\n");
	printf("\tx: %f\n", rt->cam.pos.x);
	printf("\ty: %f\n", rt->cam.pos.y);
	printf("\tz: %f\n", rt->cam.pos.z);
	printf("Orientation:\n");
	printf("\tx: %f\n", rt->cam.aim.x);
	printf("\ty: %f\n", rt->cam.aim.y);
	printf("\tz: %f\n", rt->cam.aim.z);
	printf("FOV: %d\n\n", rt->cam.fov);

	printf(RED"---------- Printing Objects -----------\n\n"CLEAR);

	int i = 0;
	while (i < rt->nb_objs)
	{
		printf(RED"--- Object #: %d ---\n"CLEAR, i);
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