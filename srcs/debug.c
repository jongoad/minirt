#include "minirt.h"

#define RED "\033[1;31m"
#define CLEAR "\033[0m"


void	print_scene_after_init(t_data *rt)
{
	int i;

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

	i = 0;
	while (i < rt->nb_objs)
	{
		printf(RED"--- Object #: %d ---\n"CLEAR, i);
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
		printf("Color**:\n");
		printf("\tr: %f\n", rt->objs[i]->color.x);
		printf("\tg: %f\n", rt->objs[i]->color.y);
		printf("\tb: %f\n", rt->objs[i]->color.z);
		printf("Brightness Ratio: %f\n", rt->objs[i]->ratio);
		printf("Radius: %f\n", rt->objs[i]->radius);
		printf("Height: %f\n", rt->objs[i]->height);
		printf("\n\n");
		i++;
	}
	i = 0;
	while (i < rt->nb_lights)
	{
		printf(RED"--- Lights #: %d ---\n"CLEAR, i);
		printf("Position:\n");
		printf("\tx: %f\n", rt->lights[i]->center.x);
		printf("\ty: %f\n", rt->lights[i]->center.y);
		printf("\tz: %f\n", rt->lights[i]->center.z);
		printf("Orientation:\n");
		printf("\tx: %f\n", rt->lights[i]->normal.x);
		printf("\ty: %f\n", rt->lights[i]->normal.y);
		printf("\tz: %f\n", rt->lights[i]->normal.z);
		printf("Colour:\n");
		printf("\tr: %d\n", rt->lights[i]->clr.r);
		printf("\tg: %d\n", rt->lights[i]->clr.g);
		printf("\tb: %d\n", rt->lights[i]->clr.b);
		printf("Color**:\n");
		printf("\tr: %f\n", rt->lights[i]->color.x);
		printf("\tg: %f\n", rt->lights[i]->color.y);
		printf("\tb: %f\n", rt->lights[i]->color.z);
		printf("Brightness Ratio: %f\n", rt->lights[i]->ratio);
		printf("Radius: %f\n", rt->lights[i]->radius);
		printf("Height: %f\n", rt->lights[i]->height);
		printf("\n\n");
		i++;
	}
}