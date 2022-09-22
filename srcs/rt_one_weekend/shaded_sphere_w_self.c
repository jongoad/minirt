#include "minirt.h"
#include <time.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

t_vec3	ray_at(t_ray_vec3 *r, float t)
{
	return add_vec3(r->orig, mult_vec3(r->dir, t));
}

typedef struct s_quadratic
{
    float	a;
    float	half_b;
    float	c;
    float	discriminant;
	float	sqrtd;
	float	root;
}	t_quadratic;

bool	hit_sphere(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec, float t_min)
{
    t_vec3			oc;
	t_quadratic		q;

	oc = sub_vec3(r->orig, o->center);
	q.a = dot_vec3(r->dir, r->dir);
	q.half_b = dot_vec3(oc, r->dir);
	q.c = dot_vec3(oc, oc) - o->radius * o->radius;
	q.discriminant = q.half_b * q.half_b - q.a * q.c;
    if (q.discriminant < 0)
        return false;	
    q.sqrtd = sqrtf(q.discriminant);
    q.root = (-q.half_b - q.sqrtd) / q.a;
// Try the other root, aka the inside of the sphere from the camera
    if (q.root < t_min || q.root > r->t_max)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
        if (q.root < t_min || q.root > r->t_max)
		{
			return false;
		}
    }
	if (q.root < rec->t) {
		rec->t = q.root;
		rec->p = ray_at(r, rec->t);
		rec->normal = div_vec3(sub_vec3(rec->p, o->center), o->radius);
	}
    return true;
}

bool	hit_sphere_debug(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec, float t_min)
{
    t_vec3			oc;
	t_quadratic		q;

	oc = sub_vec3(r->orig, o->center);
	q.a = dot_vec3(r->dir, r->dir);
	q.half_b = dot_vec3(oc, r->dir);
	q.c = dot_vec3(oc, oc) - o->radius * o->radius;
	q.discriminant = q.half_b * q.half_b - q.a * q.c;
	printf("discriminant = %.6f, ", q.discriminant);
    if (q.discriminant < 0)
	{
		printf("\n");
        return false;	
	}
    q.sqrtd = sqrtf(q.discriminant);
	printf("sqrtd = %.6f, ", q.sqrtd);
    q.root = (-q.half_b - q.sqrtd) / q.a;
	printf("root = %.6f, ", q.sqrtd);
// Try the other root, aka the inside of the sphere from the camera
    if (q.root < t_min || q.root > r->t_max)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
        if (q.root < t_min || q.root > r->t_max)
		{
			printf("\n");
            return false;
		}
    }
    rec->t = q.root;
    rec->p = ray_at(r, rec->t);
    rec->normal = div_vec3(sub_vec3(rec->p, o->center), o->radius);
	printf("\n");
    return true;
}

# define BG -1
int		ray_sphere(t_ray_vec3 *r, t_obj *sp, t_hit_rec *rec)
{
	static t_vec3		z_norm = { .x = 0.0, .y = 0.0, .z = -1.0 };
	static t_vec3		unit = { .x = 1.0, .y = 1.0, .z = 1.0 };
	t_vec3				color;
	
    if (hit_sphere(r, sp, rec, T_MIN))
	{
		// if (cos_vec3(rec->normal, r->dir) > 0)	// If in same direction, inside obj
			return ( vec3_to_color(sp->color));
		color = mult_vec3(
					add_vec3(
						unit_vec3(sub_vec3(rec->p, z_norm))
						, unit)
				, 127.999F);
        return (vec3_to_color(color));
		color = rec->p;
		sub_vec3_self(&color, z_norm);
		unit_vec3_self(&color);
		add_vec3_self(&color, unit);
		mult_vec3_self(&color, 127.999F); // 0.5F * 255
        return (vec3_to_color(color));
	}

	/* Black background */
	return (BG);
}

int		ray_sphere_debug(t_ray_vec3 *r, t_obj *sp, t_hit_rec *rec)
{
	static t_vec3		z_norm = { .x = 0.0, .y = 0.0, .z = -1.0 };
	static t_vec3		unit = { .x = 1.0, .y = 1.0, .z = 1.0 };
	t_vec3				color;
	
    if (hit_sphere_debug(r, sp, rec, T_MIN))
	{
		if (cos_vec3(rec->normal, r->dir) > 0)	// If in same direction, inside obj
			return ( vec3_to_color(sp->color) );
		color = mult_vec3(
					add_vec3(
						unit_vec3(sub_vec3(rec->p, z_norm))
						, unit)
				, 127.999F);
        return (vec3_to_color(color));
		color = rec->p;
		sub_vec3_self(&color, z_norm);
		unit_vec3_self(&color);
		add_vec3_self(&color, unit);
		mult_vec3_self(&color, 127.999F); // 0.5F * 255
        return (vec3_to_color(color));
	}

	/* Black background */
	return (BG);
}

int	apply_point_lights(t_data *rt, t_hit_rec *rec, int color)
{
	// Apply light point's contribution to perceived color

	t_vec3	vcolor;
	t_vec3	pt_to_light;
	float	dot;

	// pt_to_light = sub_vec3(rt->objs[0]->center, rt->lights[0].pos);
	pt_to_light = sub_vec3(rt->lights[0].pos, rt->objs[0]->center);
	dot = cos_vec3(rec->normal, pt_to_light);
	if (dot <= 0.0F)
		return color;
	vcolor = color_to_vec3(color);
	color = vec3_to_color(lerp_vec3(vcolor, rt->lights[0].color, dot));
	return color;
}


void	generate_sphere_shaded(t_data *rt, t_obj *sp)
{
    // Render
	t_ray_vec3	r;
	int			pixel_color;
	float		u;
	float		v;
	
	// Benchmarking
	float		start_time = (float)clock();

	// Hit Record
	t_hit_rec	rec;
	
	r.orig = rt->cam.pos;
    for (int j = 0; j < rt->img->height; ++j) {
        for (int i = 0; i < rt->img->width; ++i) {
            u = (float)(i) / (rt->img->width - 1);
            v = (float)(j) / (rt->img->height - 1);
			r.dir = sub_vec3(add3_vec3(
				rt->cam.low_left,
				mult_vec3(rt->cam.horizontal, u),
				mult_vec3(rt->cam.vertical, v)),
				rt->cam.pos);
			r.t_max = T_INF;
			rec.t = T_INF;
            pixel_color = ray_sphere(&r, sp, &rec) ;
			if (pixel_color == BG)
				pixel_color = rt->background;
			else 
            	pixel_color = apply_point_lights(rt, &rec, pixel_color);
            fill_pixel(rt->img, i, j, pixel_color);
        }
    }
	/* To test epsilon values for sphere antialiasing */
	// int j = IMG_H / 2;
	// for (int i = 0; i < rt->img->width; ++i) {
	// 	u = (float)(i) / (rt->img->width - 1);
	// 	v = (float)(j) / (rt->img->height - 1);
	// 	r.dir = sub_vec3(add3_vec3(
	// 		rt->cam.low_left,
	// 		mult_vec3(rt->cam.horizontal, u),
	// 		mult_vec3(rt->cam.vertical, v)),
	// 		rt->cam.pos);
	// 	r.t_max = T_INF;
	// 	printf("x = %d: ", i);
	// 	pixel_color = ray_sphere_debug(&r, sp, &rec);
	// 	rec.t = 0;
	// }
	display_default(rt);
	display_fps(rt, start_time);
}