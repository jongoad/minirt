#include "minirt.h"

/* Allocate memory for scene objects */
void	init_scene_allocate(t_data *rt)
{
	count_objects(rt);
	rt->objs = ft_xalloc(sizeof(t_obj *) * (rt->nb_objs + 1));
	rt->lights = ft_xalloc(sizeof(t_obj *) * (rt->nb_lights + 1));
}

/* Initialize scene using parsed object data */
void	init_scene(t_data *rt)
{
	int i;
	int obj_nb;
	int light_nb;
	int res;

	i = 0;
	obj_nb = 0;
	light_nb = 0;
	init_scene_allocate(rt);										/* Count number of objects in scene and allocate memory */
	while (rt->parse.scene[i])
	{
		res = check_tok(rt->parse.scene[i][0], rt->parse.tok);		/* Check current line of .rt file data to get index of correct function */
		if (res == 2)												/* If object is a light, increment count and initialize */
		{
			rt->parse.f2[res](rt, rt->parse.scene[i], light_nb);
			light_nb++;
		}
		else if (res >= 0)										
		{
			rt->parse.f2[res](rt, rt->parse.scene[i], obj_nb);
			if (res > 2)											/* Increment object count for non-camera, non-ambient, non-light objects */
				obj_nb++;
		}
		i++;
	}
}

/* Get initial camera angles from orientation vector */
void	init_cam_angles(t_data *rt)
{
	float res;
	t_vec3 cross_test;

	/* Initialize starting pitch */
	if (sqrt(pow(rt->cam.forward.y, 2) + pow(rt->cam.forward.z, 2)) == 0.0)			/* Check if starting vector is (0,1,0). If true, use right vector for calculation */
		rt->cam.pitch = (90 - (acos(rt->cam.forward.y /
		(sqrt(pow(rt->cam.forward.y, 2) + pow(rt->cam.forward.x, 2)))) *
		(180 / PI))) * -1.0f;
	else
		rt->cam.pitch = (90 - (acos(rt->cam.forward.y /
		(sqrt(pow(rt->cam.forward.y, 2) + pow(rt->cam.forward.z, 2)))) *
		(180 / PI))) * -1.0f;
	rt->cam.pitch = roundf_precision(rt->cam.pitch, 5);								/* Round value to 5 digit precision to remove error */

	/* Initialize starting yaw */
	rt->cam.yaw = acos(-rt->cam.forward.z / (sqrt(pow(rt->cam.forward.x, 2)
		+ pow(rt->cam.forward.z, 2)))) * (180 / PI);
	rt->cam.yaw = roundf_precision(rt->cam.yaw, 5);									/* Round value to 5 digit precision to remove error */

	/* Use cross product test to find which side of Zaxis the vector falls on */
	cross_test = cross_vec3(vec3(0,0,-1),													
		unit_vec3(vec3(rt->cam.forward.x, 0, rt->cam.forward.z)));
	res = roundf_precision(cross_test.y, 5);
	if (res > 0)																	/* If Vector falls on -x side of Zaxis adjust appropriately */
		rt->cam.yaw = 360 - rt->cam.yaw;
}

/* Intialize toggle variables based on BONUS status */
void	init_toggle(t_data *rt)
{
	if (BONUS)														/* If BONUS is true, then set bonus features to be toggled on */
	{
		rt->toggle.is_normal = true;
		rt->toggle.is_texture = true;
		rt->toggle.is_specular = true;
	}
	else															/* Otherwise set bonus features to off */
	{
		rt->toggle.is_normal = false;
		rt->toggle.is_texture = false;
		rt->toggle.is_specular = false;
	}
	rt->toggle.is_light_halo = false;
	rt->toggle.is_display_debug = false;
	rt->toggle.is_left_click = false;
}

/* Split input and initialize objects */
void	rt_init(t_data *rt, char *filepath)
{
	rt->background = int_to_color(BLACK);
	rt->selected = 0;
	rt_init_mlx(rt, filepath);														/* Setup mlx window data*/
	rt_init_img(rt);																/* Setup mlx image data */
	init_parse_fct_ptrs(rt);														/* Setup function pointer array for object initialization */
	init_scene(rt);																	/* Setup scene objects using parsed .rt scene data */
	parse_free(&rt->parse);															/* Free all memory from parsing and object initialization */
	init_cam_angles(rt);															/* Get camera transform angles from orientation vector */
	init_toggle(rt);																/* Set initial toggle variable values */
}
