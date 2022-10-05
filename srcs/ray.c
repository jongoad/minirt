#include "minirt.h"

/**
 * @brief  Generate a primary ray for a specific pixel, returns the 
 * 
 * @return obj_id of the closest hit obj 
 */
int	cast_ray_at_pixel(t_data *rt, int x, int y)
{
	t_ray_vec3	r;
	float		u;
	float		v;
	t_hit_rec	rec;
	int			i_obj;	// To traverse objs array
	
	r.orig = rt->cam.pos;
	u = (float)(x) / (rt->img->width - 1);
	v = (float)(y) / (rt->img->height - 1);
	r.dir = sub_vec3(add3_vec3(
		rt->cam.low_left,
		mult_vec3(rt->cam.horizontal, u),
		mult_vec3(rt->cam.vertical, v)),
		rt->cam.pos);
	rec.color = color_to_vec3(rt->background);
	rec.t = T_MAX;
	rec.hit_anything = false;
	i_obj = -1;
	while (++i_obj < rt->nb_objs)
	{
		if (rt->objs[i_obj]->type == T_LIGHT)
			continue ;
		if (rt->objs[i_obj]->hit(&r, rt->objs[i_obj], &rec))
			rec.obj_id = i_obj;
	}
	if (rec.hit_anything)
		return (rec.obj_id);
	return (NO_HIT);
}
