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

bool	hit_sphere_no_hit_rec(t_ray_vec3 *r, t_obj *o)
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
	return true;
}

bool	hit_sphere(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
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
    if (q.root < T_MIN || q.root > r->t_max)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
        if (q.root < T_MIN || q.root > r->t_max)
		{
			return false;
		}
    }
	if (q.root < rec->t) {
		rec->hit_anything = true;
		rec->t = q.root;
		rec->p = ray_at(r, rec->t);
		rec->normal = div_vec3(sub_vec3(rec->p, o->center), o->radius);
		rec->color = o->color;
    	return true;
	}
	return false;
}

bool	hit_sphere_debug(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
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
    if (q.root < T_MIN || q.root > r->t_max)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
        if (q.root < T_MIN || q.root > r->t_max)
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
	float				tmp;
	
	tmp = rec->t;
    if (hit_sphere(r, sp, rec) && rec->t != tmp)
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
	
    if (hit_sphere_debug(r, sp, rec))
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

int	apply_single_point_light(t_data *rt, t_hit_rec *rec, int color)
{
	// Apply light point's contribution to perceived color

	t_vec3	vcolor;
	t_vec3	pt_to_light;
	double	t;

	// pt_to_light = sub_vec3(rt->objs[0]->center, rt->lights[0].pos);
	pt_to_light = sub_vec3(rt->lights[0].pos, rt->objs[0]->center);
	t = cos_vec3(rec->normal, pt_to_light);
	if (t <= 0.0F)
		return color;
	vcolor = color_to_vec3(color);
	color = vec3_to_color(lerp_vec3(vcolor, rt->lights[0].color, t));
	return color;
}

int	apply_point_lights(t_data *rt, t_obj *o, t_hit_rec *rec, int color)
{
	// Apply light point's contribution to perceived color

	t_vec3		vcolor;
	t_ray_vec3	pt_to_light;
	t_hit_rec	rec2;
	t_vec3		diff;
	float		t;
	int			i;

	// FIXME: to remove
	(void) o;
	pt_to_light.dir = rec->p;
	pt_to_light.orig = rt->lights[0].pos;

	// Test for hard shadows
	rec2.t = T_INF;
	i = 0;
	while (i < rt->nb_objs)
	{
		// if (rt->objs[i]->hit(&pt_to_light, rt->objs[i], &rec2))
		if (rt->objs[i]->hit_no_rec(&pt_to_light, rt->objs[i]))
			return WHITE;
		i++;
	}
	diff = sub_vec3(pt_to_light.dir, pt_to_light.orig);
	t = cos_vec3(rec->normal, diff);
	if (t <= 0.0F)
		return color;
	vcolor = color_to_vec3(color);
	color = vec3_to_color(lerp_vec3(vcolor, rt->lights[0].color, t));
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

	// To traverse objs array
	int		i_obj;
	
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
			rec.color = color_to_vec3(rt->background);
			rec.t = T_INF;
			rec.hit_anything = false;
			i_obj = 0;
			pixel_color = rt->background;
			while (i_obj < rt->nb_objs)
			{
				if (rt->objs[i_obj]->hit(&r, rt->objs[i_obj], &rec))
					rec.obj_id = i_obj;
				i_obj++;
			}
            // pixel_color = ray_sphere(&r, sp, &rec) ;
            // pixel_color = ray_sphere(&r, rt->objs[1], &rec) ;
			if (rec.hit_anything)
				pixel_color = vec3_to_color(rec.color);
			// if (pixel_color == BG)
			// 	pixel_color = rt->background;
			// else 
			if (pixel_color != rt->background)
            	pixel_color = apply_point_lights(rt, rt->objs[rec.obj_id], &rec, pixel_color);
            	// pixel_color = apply_single_point_light(rt, &rec, pixel_color);
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
	(void)sp;
	display_default(rt);
	display_fps(rt, start_time);
}