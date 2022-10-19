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
		rt->objs[i]->pos = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(rt->objs[i]->pos_ref, T_POINT), rt->cam.inv_project));
	i = -1;
	while (++i < rt->nb_lights)
		rt->lights[i]->pos = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(rt->lights[i]->pos_ref, T_POINT), rt->cam.inv_project));
}

void	render_scene(t_data *rt, t_obj *sp)
{
    // Render
	t_ray_vec3	r;
	int			pixel_color;

	// Single pixels debug
	int		print_pixel = 10;
	t_point	p_debug = {.x = 0, .y = 0, .z = -3, .w = 0};

	p_debug = sub_vec3(p_debug, rt->cam.pos);
	printf("\np_debug - cam.pos = (%f, %f, %f)\n", p_debug.x, p_debug.y, p_debug.z);
	printf("length = %f\n", length_vec3(p_debug));
	
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
			rec.color = color_to_vec3(rt->background);
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

			if (fabs(length_vec3(r.dir) - 1.0F) > 0.01F)
			{
				printf("length = %f\n", length_vec3(r.dir));
				printf("r.dir: (%f, %f, %f)\n", r.dir.x, r.dir.y, r.dir.z);
			}

			// Single pixels debug
			if (rec.hit_anything && print_pixel)
			{
				printf("\n(%d,%d)\n", i, j);
				printf("rec->obj_id = %d\n", rec.obj_id);
				printf("rec->t = %f\n", rec.t);
				printf("rec->inside_surface? %d\n", rec.inside_surface);
				printf("cam.pos: (%f, %f, %f)\n", rt->cam.pos.x, rt->cam.pos.y, rt->cam.pos.z);
				print_pixel--;
			}



			if (rec.hit_anything)
            	pixel_color = apply_point_lights(rt, &rec, vec3_to_color(rec.color));
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
