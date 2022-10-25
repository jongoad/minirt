#include "minirt.h"
#include <time.h>

bool	hit_anything(t_data *rt, t_ray_vec3 *pt_to_light, t_hit_rec *rec)
{
	int		i;

	i = -1;
	while (++i < rt->nb_objs)
	{
		if (rt->objs[i]->hit(pt_to_light, rt->objs[i], rec))
			return (true);
	}
	return (false);
}

void	objects_apply_inverse_view_matrix(t_data *rt)
{
	int		i;

	i = -1;
	while (++i < rt->nb_objs)
		rt->objs[i]->pos = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(rt->objs[i]->pos_ref, T_POINT), rt->cam.view));
	i = -1;
	while (++i < rt->nb_lights)
		rt->lights[i]->pos = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(rt->lights[i]->pos_ref, T_POINT), rt->cam.view));
}

void	render_scene(t_data *rt, t_obj *sp)
{
    // Render
	t_ray_vec3	r;
	int			pixel_color;
	
	// Benchmarking
	// float		start_time = (float)clock();

	// Hit Record
	t_hit_rec	rec;

	// To traverse objs array
	int		i_obj;
	// FIXME: might be broken ? question mark
	// objects_apply_inverse_view_matrix(rt);

	
	r.orig = rt->cam.pos;
	// r.orig = vec3(0,0,0);
    for (int j = 0; j < rt->img->height; ++j) {
        for (int i = 0; i < rt->img->width; ++i) {
			r.dir = rt->cam.rays[j][i];
			rec.color = int_to_color(rt->background);
			rec.t = T_MAX;
			rec.hit_anything = false;

			pixel_color = rt->background;

			i_obj = -1;
			while (++i_obj < rt->nb_objs)
			{
				if (rt->objs[i_obj]->type == T_LIGHT)
					continue ;
				if (rt->objs[i_obj]->hit(&r, rt->objs[i_obj], &rec))
				{
					rec.obj_id = i_obj;
				}
			}

			if (rec.hit_anything)
            	pixel_color = apply_point_lights(rt, &rec, color_to_int(rec.color));
			if (rt->apply_light_halos == true)
				pixel_color = apply_light_halos(rt, &r, &rec, pixel_color, i, j);
			
            fill_pixel(rt->img, i, j, pixel_color);
        }
    }
	(void)sp;

	display_default(rt);
	// display_fps(rt, start_time);
	print_data_to_screen(rt);
}
