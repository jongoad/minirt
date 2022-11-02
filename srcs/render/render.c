#include "minirt.h"
#include <time.h>

bool	hit_anything(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec)
{
	int		i;

	i = -1;
	while (++i < rt->nb_objs)
	{
		if (rt->objs[i]->hit(r, rt->objs[i], rec))
		{
			rec->obj_id = i;
		}
	}
	return (rec->hit_anything);
}

/* Get final colour values for a single pixel */
static inline t_color	render_pixel(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec)
{
	register t_color	pixel_color;

	rec->t = T_MAX;
	rec->hit_anything = false;
	if (hit_anything(rt, r, rec))
	{
		// if (rt->toggle.is_texture)
		// 	rec->color = pattern_at_image(sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->earth, T_SPH);

		rec->color = obj_get_color(rt, sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->objs[rec->obj_id]);
		if (rt->toggle.is_normal)
			rec->normal = obj_get_normal(rec->normal, sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->objs[rec->obj_id]);
		// rec->normal = perturb_normal(rec->normal, normal_image_to_vec3(uv_at(sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->earth_normal, T_SPH), rt->earth_normal.image));
		/* Toggle point lights */
		if (rt->toggle.is_point_light)
			pixel_color = apply_point_lights(rt, rec, rec->color);
	}
	else 
		pixel_color = rt->background;
	//Can this be moved into render control?
	if (rt->toggle.is_light_halo)
		pixel_color = apply_light_halos(rt, r, rec, pixel_color);
	return (pixel_color);
}

/* Render current scene and displayto screen */
void	render_scene(t_data *rt)
{
	t_ray_vec3	r;
	t_hit_rec	rec;
	int			i;
	int			j;

	r.orig = rt->cam.pos;
	j = -1;
    while (++j < rt->img->height)
	{
		i = -1;
        while (++i < rt->img->width)
		{
			r.dir = rt->cam.rays[j][i];
            fill_pixel(rt->img, i, j, render_pixel(rt, &r, &rec));
        }
    }

	display_default(rt);
	print_data_to_screen(rt);
}
