#include "minirt.h"

#define RED "\033[1;31m"
#define CLEAR "\033[0m"

/* Print out all objects in scene */
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
		printf("Type: %c\n", rt->objs[i]->type);
		printf("Position:\n");
		printf("\tx: %f\n", rt->objs[i]->pos.x);
		printf("\ty: %f\n", rt->objs[i]->pos.y);
		printf("\tz: %f\n", rt->objs[i]->pos.z);
		printf("Orientation:\n");
		printf("\tx: %f\n", rt->objs[i]->fwd.x);
		printf("\ty: %f\n", rt->objs[i]->fwd.y);
		printf("\tz: %f\n", rt->objs[i]->fwd.z);
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
		printf("\tx: %f\n", rt->lights[i]->pos.x);
		printf("\ty: %f\n", rt->lights[i]->pos.y);
		printf("\tz: %f\n", rt->lights[i]->pos.z);
		printf("Orientation:\n");
		printf("\tx: %f\n", rt->lights[i]->fwd.x);
		printf("\ty: %f\n", rt->lights[i]->fwd.y);
		printf("\tz: %f\n", rt->lights[i]->fwd.z);
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

/* Print out current data for camera */
void	print_cam_data(t_data *rt)
{
	printf(RED"------- Current Camera  -------\n\n"CLEAR);
	printf(RED"--- Position ---\n"CLEAR);
	printf("x: %f\ny: %f\nz: %f\n\n", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z);
	printf(RED"--- Orientation ---\n"CLEAR);
	printf("x: %f\ny: %f\nz: %f\n\n", rt->cam.forward.x, rt->cam.forward.y, rt->cam.forward.z);
	printf(RED"--- Other ---\n"CLEAR);
	printf("FOV: %d\n", rt->cam.fov);
	printf("Near Clip: %f\n", rt->cam.near);
	printf("Far Clip: %f\n\n", rt->cam.far);
}

/* Print out current data for an individual object */
void	print_obj_data(t_obj *obj)
{
	printf(RED"------- Selected Object Data -------\n\n"CLEAR);
	printf ("\tType: %c\n", obj->type);
	printf("\tRadius: %f\n", obj->radius);
	printf("\tWidth: %f\n", obj->width);
	printf("\tHeight: %f\n\n", obj->height); 
	printf(RED"--- Position ---\n"CLEAR);
	printf("\tx: %f\n\ty: %f\n\tz: %f\n\n", obj->pos.x, obj->pos.y, obj->pos.z);
	printf(RED"--- Orientation ---\n"CLEAR);
	printf("\tx: %f\n\ty: %f\n\tz: %f\n\n", obj->fwd.x, obj->fwd.y, obj->fwd.z);
	printf(RED"--- Color ---\n"CLEAR);
	printf("\tr: %d\n\tg: %d\n\tb: %d\n\n", obj->clr.r, obj->clr.g, obj->clr.b);
}