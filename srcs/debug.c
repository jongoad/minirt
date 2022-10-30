#include "minirt.h"

#define RED_C "\033[1;31m"
#define CLEAR "\033[0m"

void	print_obj_info(t_data *rt, int id)
{
	printf(RED_C"--- Object #: %d ---\n"CLEAR, id);
	printf("Type: %c\n", rt->objs[id]->type);
	printf("Position:\n");
	printf("\tx: %f\n", rt->objs[id]->pos.x);
	printf("\ty: %f\n", rt->objs[id]->pos.y);
	printf("\tz: %f\n", rt->objs[id]->pos.z);
	printf("Forward:\n");
	printf("\tx: %f\n", rt->objs[id]->fwd.x);
	printf("\ty: %f\n", rt->objs[id]->fwd.y);
	printf("\tz: %f\n", rt->objs[id]->fwd.z);
	printf("Up:\n");
	printf("\tx: %f\n", rt->objs[id]->up.x);
	printf("\ty: %f\n", rt->objs[id]->up.y);
	printf("\tz: %f\n", rt->objs[id]->up.z);
	printf("Right:\n");
	printf("\tx: %f\n", rt->objs[id]->right.x);
	printf("\ty: %f\n", rt->objs[id]->right.y);
	printf("\tz: %f\n", rt->objs[id]->right.z);
	printf("Colour:\n");
	printf("\tr: %d\n", rt->objs[id]->clr.r);
	printf("\tg: %d\n", rt->objs[id]->clr.g);
	printf("\tb: %d\n", rt->objs[id]->clr.b);
	printf("Brightness Ratio: %f\n", rt->objs[id]->ratio);
	printf("Radius: %f\n", rt->objs[id]->radius);
	printf("Height: %f\n", rt->objs[id]->half_height);
	printf("\n\n");
}

// /* Print out all objects in scene */
void	print_scene_after_init(t_data *rt)
{
	int i;

	printf(RED_C"------- Printing Initialized Scene -------\n\n"CLEAR);

	printf(RED_C"--- Ambient Light ---\n"CLEAR);
	printf("Intensity: %f\n", rt->ambient.ratio);
	printf("Colour:\n");
	printf("\tr: %d\n", rt->ambient.clr.r);
	printf("\tg: %d\n", rt->ambient.clr.g);
	printf("\tb: %d\n", rt->ambient.clr.b);

	printf(RED_C"\n--- Camera ---\n"CLEAR);
	printf("Position:\n");
	printf("\tx: %f\n", rt->cam.pos.x);
	printf("\ty: %f\n", rt->cam.pos.y);
	printf("\tz: %f\n", rt->cam.pos.z);
	printf("Orientation:\n");
	printf("\tx: %f\n", rt->cam.forward.x);
	printf("\ty: %f\n", rt->cam.forward.y);
	printf("\tz: %f\n", rt->cam.forward.z);
	printf("FOV: %d\n\n", rt->cam.fov);

	printf(RED_C"---------- Printing Objects -----------\n\n"CLEAR);

	i = 0;
	while (i < rt->nb_objs)
	{

		i++;
	}
	i = 0;
	while (i < rt->nb_lights)
	{
		printf(RED_C"--- Lights #: %d ---\n"CLEAR, i);
		printf("Position:\n");
		printf("\tx: %f\n", rt->lights[i]->pos.x);
		printf("\ty: %f\n", rt->lights[i]->pos.y);
		printf("\tz: %f\n", rt->lights[i]->pos.z);
		printf("Colour:\n");
		printf("\tr: %d\n", rt->lights[i]->clr.r);
		printf("\tg: %d\n", rt->lights[i]->clr.g);
		printf("\tb: %d\n", rt->lights[i]->clr.b);
		printf("Brightness Ratio: %f\n", rt->lights[i]->ratio);
		printf("\n\n");
		i++;
	}
}

/* Print out current data for camera */
void	print_cam_data(t_data *rt)
{
	printf(RED_C"------- Current Camera  -------\n\n"CLEAR);
	printf(RED_C"--- Position ---\n"CLEAR);
	printf("x: %f\ny: %f\nz: %f\n\n", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z);
	printf(RED_C"--- Orientation ---\n"CLEAR);
	printf("x: %f\ny: %f\nz: %f\n\n", rt->cam.forward.x, rt->cam.forward.y, rt->cam.forward.z);
	printf(RED_C"--- Other ---\n"CLEAR);
	printf("FOV: %d\n", rt->cam.fov);
}

/* Print out current data for an individual object */
void	print_obj_data(t_obj *obj)
{
	printf(RED_C"------- Selected Object Data -------\n\n"CLEAR);
	printf ("\tType: %c\n", obj->type);
	printf("\tRadius: %f\n", obj->radius);
	printf("\tWidth: %f\n", obj->width);
	printf("\tHeight: %f\n\n", obj->half_height); 
	printf(RED_C"--- Position ---\n"CLEAR);
	printf("\tx: %f\n\ty: %f\n\tz: %f\n\n", obj->pos.x, obj->pos.y, obj->pos.z);
	printf(RED_C"--- Orientation ---\n"CLEAR);
	printf("\tx: %f\n\ty: %f\n\tz: %f\n\n", obj->fwd.x, obj->fwd.y, obj->fwd.z);
	printf(RED_C"--- Color ---\n"CLEAR);
	printf("\tr: %d\n\tg: %d\n\tb: %d\n\n", obj->clr.r, obj->clr.g, obj->clr.b);
}

void	print_data_to_screen(t_data *rt)
{

	char o[150], c[150], ca[150], cb[150], cc[150], r[150], r2[150];

	int x = 400;
	int y = 400;

	/* Object 0 */
	sprintf(o, "pos: x: %f y: %f z: %f", rt->objs[0]->pos.x, rt->objs[0]->pos.y, rt->objs[0]->pos.z);
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 100, RED, "Object Data:");
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 115, RED, o);

	/* Camera */
	sprintf(c, "pos: x: %f y: %f z: %f", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z);
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 140, RED, "Camera Data:");
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 155, RED, c);
	sprintf(ca, "aim: x: %f y: %f z: %f", rt->cam.forward.x, rt->cam.forward.y, rt->cam.forward.z);
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 170, RED, ca);
	sprintf(cb, "tilt: %f", rt->cam.pitch);
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 185, RED, cb);
	sprintf(cc, "pan: %f", rt->cam.yaw);
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 200, RED, cc);


	/* Ray */
	sprintf(r, "aim: x: %f y: %f z: %f", rt->cam.rays[y][x].x, rt->cam.rays[y][x].y, rt->cam.rays[y][x].z);
	sprintf(r2, "ray[%i][%i]", y, x);

	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 225, RED, "Ray Data:");
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 240, RED, r2);
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 255, RED, r);
}

