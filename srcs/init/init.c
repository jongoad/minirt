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
	printf("nb_objs = %d\n", rt->nb_objs);
	printf("nb_lights = %d\n", rt->nb_lights);

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

void	init_cam_angles(t_data *rt, t_vec3 up, t_vec3 right)
{
	double dprod = (rt->cam.forward.y * up.y) + (rt->cam.forward.z * up.z);
	double mag_fwd = sqrt(pow(rt->cam.forward.y, 2) + pow(rt->cam.forward.z, 2));
	double mag_up = sqrt(pow(up.y, 2) + pow(up.z, 2));

	rt->cam.tilt = 90 - (acos(dprod / (mag_fwd * mag_up)) * (180 / PI));

	dprod = (rt->cam.forward.x * right.x) + (rt->cam.forward.z * right.z);
	mag_fwd = sqrt(pow(rt->cam.forward.x, 2) + pow(rt->cam.forward.z, 2));
	double mag_right = sqrt(pow(right.x, 2) + pow(right.z, 2));

	rt->cam.pan = 90 - (acos(dprod / (mag_fwd * mag_right)) * (180 / PI));
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
	init_cam_angles(rt, vec3(0,1,0), vec3(1,0,0));
}
