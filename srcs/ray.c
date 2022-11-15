#include "minirt.h"

/* Casts a ray at a given pixel, returns a pointer to the closest object */
t_obj	*cast_ray_at_pixel(t_data *rt, int x, int y)
{
	t_hit_rec	rec;
	t_ray		r;
	
	r.orig = rt->cam.pos;
	r.dir = rt->cam.rays[y][x];
	rec.color = rt->background;
	rec.t = T_MAX;
	rec.hit_anything = false;
	rec.obj = NULL;
	hit_anything(rt, &r, &rec);
	hit_lights(rt, &r, &rec);
	return (rec.obj);
}

/* Gives you the point on the ray `r' at distance `t' */
t_vec3	ray_at(t_ray *r, float t)
{
	return add_vec3(r->orig, mult_vec3(r->dir, t));
}

/* Reflects ray `dir' about the `normal' axis */
t_vec3	reflect_ray(t_vec3 dir, t_vec3 normal)
{
	return (sub_vec3(mult_vec3(normal, 2 * dot_vec3(dir, normal)), dir));
}

/* Projects vector `a' onto vector 'b' */
t_vec3	project_a_on_b(t_vec3 a, t_vec3 b)
{
	return (mult_vec3(b, dot_vec3(a, b) / dot_vec3(b, b)));
}
