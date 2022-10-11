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
	int			i_obj;	// To traverse objs array
	
	r.orig = rt->cam.pos;
	r.dir = rt->cam.rays[y][x];
	rec.color = color_to_vec3(rt->background);
	rec.t = T_MAX;
	rec.hit_anything = false;
	i_obj = -1;
	while (++i_obj < rt->nb_objs)
		if (rt->objs[i_obj]->hit(&r, rt->objs[i_obj], &rec))
			rec.obj_id = i_obj;
	if (rec.hit_anything)
		return (rec.obj_id);
	return (NO_HIT);
}

t_vec3	ray_at(t_ray_vec3 *r, float t)
{
	return add_vec3(r->orig, mult_vec3(r->dir, t));
}
