#include "minirt.h"

/**
 * @brief  Generate a primary ray for a specific pixel, returns the 
 * 
 * @return obj_id of the closest hit obj 
 */
int	cast_ray_at_pixel(t_data *rt, int x, int y)
{
	t_ray_vec3	r;
	t_hit_rec	rec;
	int			i;	// To traverse objs array
	
	r.orig = rt->cam.pos;
	r.dir = rt->cam.rays[y][x];
	rec.color = int_to_color(rt->background);
	rec.t = T_MAX;
	rec.hit_anything = false;
	i = -1;
	rec.obj_id = i;
	while (++i < rt->nb_objs)
	{
		// printf("i = %d\n", i);
		if (rt->objs[i]->hit(&r, rt->objs[i], &rec))
		{
			rec.obj_id = i;
			// printf("Hit ! rec.obj_id = %d\n", rec.obj_id);
		}
		// printf("rec.obj_id = %d\n", rec.obj_id);
	}
	if (rec.hit_anything)
		return (rec.obj_id);
	return (NO_HIT);
}

t_vec3	ray_at(t_ray_vec3 *r, float t)
{
	return add_vec3(r->orig, mult_vec3(r->dir, t));
}
