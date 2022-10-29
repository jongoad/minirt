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

static inline int	render_pixel(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec)
{
	int			pixel_color;

	rec->t = T_MAX;
	rec->hit_anything = false;
	pixel_color = rt->background;
	if (hit_anything(rt, r, rec))
		pixel_color = apply_point_lights(rt, rec, color_to_int(rec->color));
	if (rt->apply_light_halos == true)
		pixel_color = apply_light_halos(rt, r, rec, pixel_color);
	return (pixel_color);
}

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
