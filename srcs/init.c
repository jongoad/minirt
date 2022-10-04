#include "minirt.h"

static void	rt_init_camera(t_data *rt)
{
    rt->cam.view_h = 1.0F;
    rt->cam.view_w = ASPECT_RATIO * rt->cam.view_h;
    rt->cam.z_offset = 1.0F;
    rt->cam.pos = vec3(0, 0, 0);
    rt->cam.horizontal = vec3(-rt->cam.view_w, 0, 0);
    rt->cam.vertical = vec3(0, -rt->cam.view_h, 0);
    rt->cam.low_left = sub_vec3(rt->cam.pos, div_vec3(rt->cam.horizontal, 2));
	sub_vec3_self(&(rt->cam.low_left), div_vec3(rt->cam.vertical, 2));
	sub_vec3_self(&(rt->cam.low_left), vec3(0, 0, rt->cam.z_offset));
}

static void	rt_init_lights(t_data *rt) {
	int	i = 0;

	rt->ambt_light = mult_vec3(vec3(255, 255, 255), 0.0F);
	rt->lights = ft_xalloc(sizeof(t_light_pt) * rt->nb_lights);
	rt->lights[i].color = color_to_vec3(WHITE);
	rt->lights[i].pos = vec3(0.0F, 3.0F, -1.0F);
	i++;
	// rt->lights[i].color = color_to_vec3(RED);
	// rt->lights[i].pos = vec3(0.0F, -3.0F, -1.0F);
	// i++;
	// rt->lights[i].color = color_to_vec3(BLUE);
	// rt->lights[i].pos = vec3(0.0F, 0.0F, -2.0F);
	// i++;
	rt->nb_lights = i;
}

static void	rt_init_objs(t_data *rt)
{
	int	i = 0;
	
	rt->objs = ft_xalloc(sizeof(t_obj *) * (rt->nb_objs + 1));
	// rt->objs[0] = new_cylinder(vec3(0.0F, 0.0F, -3.0F), vec3(0, 1, 1), 0.5F, 2.0F, color_to_vec3(ORANGE));
	// rt->objs[0]->color = lerp_vec3(rt->objs[0]->color, rt->ambt_light, 0.5F);	
	rt->objs[i] = new_sphere(vec3(0, -0.7F, -1.0F), 0.4F, color_to_vec3(PINK));
	rt->objs[i]->color = lerp_vec3(rt->objs[i]->color, rt->ambt_light, 0.5F);
	i++;
	rt->objs[i] = new_sphere(vec3(0.0F, 0.0F, -1.0F), 0.2F, color_to_vec3(YELLOW));
	rt->objs[i]->color = lerp_vec3(rt->objs[i]->color, rt->ambt_light, 0.5F);
	i++;
	rt->objs[i] = new_sphere(vec3(0.5F, -0.5F, -1.0F), 0.3F, color_to_vec3(CYAN));
	rt->objs[i]->color = lerp_vec3(rt->objs[i]->color, rt->ambt_light, 0.5F);
	i++;
	// rt->objs[i] = new_plane(vec3(0.0F, -0.7F, -5.0F), vec3(1, 1, 1), color_to_vec3(GREEN));
	// rt->objs[i]->color = lerp_vec3(rt->objs[i]->color, rt->ambt_light, 0.5F);
	// i++;
	rt->objs[i] = new_cylinder(vec3(0.0F, 0.0F, -3.0F), vec3(0, 1, 1), 0.5F, 0.5F, color_to_vec3(ORANGE));
	rt->objs[i]->color = lerp_vec3(rt->objs[i]->color, rt->ambt_light, 0.5F);	
	i++;
	rt->nb_objs = i;
}

static void	rt_init_img(t_data *rt)
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

static void	rt_init_mlx(t_data *rt, char *filename)
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

void	rt_init(t_data *rt, char *filename)
{
	rt->background = lerp_color(WHITE, 0.2);
	rt_init_mlx(rt, filename);
	rt_init_img(rt);
	rt_init_lights(rt);
	rt_init_camera(rt);
	rt_init_objs(rt);

	// FIXME: temporarily, the default item selected is the first sphere
	rt->selected_obj_id = 0;
	
	return ;
}
