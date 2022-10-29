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
	
	r.orig = rt->cam.pos;
	r.dir = rt->cam.rays[y][x];
	rec.color = rt->background;
	rec.t = T_MAX;
	rec.hit_anything = false;
	rec.obj_id = NO_HIT;
	if (hit_anything(rt, &r, &rec))
		return (rec.obj_id);
	return (NO_HIT);
}

t_vec3	ray_at(t_ray_vec3 *r, float t)
{
	return add_vec3(r->orig, mult_vec3(r->dir, t));
}

// t_vec3	reflect_ray(t_vec3 dir, t_vec3 normal)
// {
// 	return add_vec3(r->orig, mult_vec3(r->dir, t));
// }

t_vec3	project_a_on_b(t_vec3 a, t_vec3 b)
{
	return (mult_vec3(b, dot_vec3(a, b) / dot_vec3(b, b)));
}
