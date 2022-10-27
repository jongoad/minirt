#include "minirt.h"

void	rt_init_mlx(t_data *rt, char *filename)
{
	rt->mlx_ptr = mlx_init();
	if (!rt->mlx_ptr)
	{
		exit_on_err("mlx: mlx_init() error \n");
	}
	rt->win_name = ft_strjoin_free(
			ft_get_last_token(filename, '/'), " - minirt");
	rt->win_ptr = mlx_new_window(
			rt->mlx_ptr, IMG_W, IMG_H, rt->win_name);
	if (!rt->win_ptr)
	{
		exit_on_err("mlx: mlx_new_window() error \n");
	}
}

void	rt_init_img(t_data *rt)
{
	t_img	*img;
	
	rt->img = ft_xalloc(sizeof(t_img));
	img = rt->img;
	img->width = IMG_W;
	img->height = IMG_H;
	img->img_ptr = mlx_new_image(rt->mlx_ptr, img->width, img->height);
	img->data_addr = mlx_get_data_addr(
			img->img_ptr, &img->bpp, &img->line_len, &img->endian);
}

/* Split input and initialize objects */
void	init_scene(t_data *rt)
{
	int i;
	int obj_nb;
	int light_nb;
	int res;

	i = 0;
	obj_nb = 0;
	light_nb = 0;
	init_parse_fct_ptrs(rt);
	count_objects(rt);
	// FIXME: to remove
	// printf("nb_objs = %d\n", rt->nb_objs);
	// printf("nb_lights = %d\n", rt->nb_lights);

	rt->objs = ft_xalloc(sizeof(t_obj *) * (rt->nb_objs + 1));
	rt->lights = ft_xalloc(sizeof(t_obj *) * (rt->nb_lights + 1));
	while (rt->parse.scene[i])
	{
		res = check_tok(rt->parse.scene[i][0], rt->parse.tok);
		if (res == 2)
		{
			rt->parse.f2[res](rt, rt->parse.scene[i], light_nb);
			light_nb++;
		}
		else
		{
			rt->parse.f2[res](rt, rt->parse.scene[i], obj_nb);
			if (res > 2)
				obj_nb++;
		}
		i++;
	}
}

/* Round a float at a specified precision */
float roundf_precision(float n, float p)
{
	double res;

	res = round(n * p);
	return (res / p);
}

/* Get initial camera angles from orientation vector */
void	init_cam_angles(t_data *rt)
{
	/* Init pitch */
	if (sqrt(pow(rt->cam.forward.y, 2) + pow(rt->cam.forward.z, 2)) == 0.0)
		rt->cam.pitch = (90 - (acos(rt->cam.forward.y / (sqrt(pow(rt->cam.forward.y, 2)
			+ pow(rt->cam.forward.x, 2)))) * (180 / PI))) * -1.0f;
	else
		rt->cam.pitch = (90 - (acos(rt->cam.forward.y / (sqrt(pow(rt->cam.forward.y, 2)
			+ pow(rt->cam.forward.z, 2)))) * (180 / PI))) * -1.0f;
	rt->cam.pitch = roundf_precision(rt->cam.pitch, 5);

	/* Init yaw */
	rt->cam.yaw = acos(-rt->cam.forward.z / (sqrt(pow(rt->cam.forward.x, 2)
		+ pow(rt->cam.forward.z, 2)))) * (180 / PI);
	rt->cam.yaw = roundf_precision(rt->cam.yaw, 5);
	t_vec3 cross_test = cross_vec3(vec3(0,0,-1),
		unit_vec3(vec3(rt->cam.forward.x, 0, rt->cam.forward.z)));
	float res = roundf_precision(cross_test.y, 5);
	if (res > 0)		/* Vector falls on -x side */
		rt->cam.yaw = 360 - rt->cam.yaw;
}

/* Split input and initialize objects */
void	rt_init(t_data *rt, char *filepath)
{
	// FIXME: to remove, for testing purposes
	rt->background = lerp_color(WHITE, 0.2);
	rt->selected_obj_id = 0;
	rt_init_mlx(rt, filepath);
	rt_init_img(rt);
	init_scene(rt);
	parse_free(&rt->parse);
	init_cam_angles(rt);
}
