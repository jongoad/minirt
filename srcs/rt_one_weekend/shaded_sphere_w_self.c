#include "minirt.h"
#include <time.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

t_vec3	ray_at(t_ray_vec3 *r, float t)
{
	return add_vec3(r->orig, mult_vec3(r->dir, t));
}

float hit_sphere_rt(t_vec3 *sp_center, float radius2, t_ray_vec3 *r) {
    t_vec3	oc;
    float	a;
    float	half_b;
    float	c;
    float	discriminant;

	oc = sub_vec3(r->orig, *sp_center);
	a = dot_vec3(r->dir, r->dir);
	half_b = dot_vec3(oc, r->dir);
	c = dot_vec3(oc, oc) - radius2;
	discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return -1.0F;
	return (-half_b - sqrtf(discriminant) ) / a; 
	// Only return the smallest value, i.e. the closest
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
            return false;
    }
    rec->t = q.root;
    rec->p = ray_at(r, rec->t);
    rec->normal = div_vec3(sub_vec3(rec->p, o->center), o->radius);
    return true;
}

int		ray_color_sphere(t_ray_vec3 *r, t_vec3 *sp_center)
{
	static t_vec3		z_norm = { .x = 0.0, .y = 0.0, .z = -1.0 };
	static t_vec3		unit = { .x = 1.0, .y = 1.0, .z = 1.0 };
    t_vec3			unit_direction;
	t_vec3			color;
	
	float	radius2 = 0.5F * 0.5F;
	float	t = hit_sphere_rt(sp_center, radius2, r);

    if (t > 0.0F)
	{
		color = add_vec3(r->orig, mult_vec3(r->dir, t));
		sub_vec3_self(&color, z_norm);
		unit_vec3_self(&color);
		add_vec3_self(&color, unit);
		mult_vec3_self(&color, 127.999F); // 0.5F * 255
        return (vec3_to_color(&color));
	}

	/* Black background */
	return (WHITE);

	/* Funky background */
	static float	h_divider = 1.0f / (IMG_H - 1);
    static float	w_divider = 1.0f / (IMG_W - 1);


	unit_direction = unit_vec3(r->dir);
	color.x = 255.0F * fabs(unit_direction.x * 255) * w_divider;
	color.y = 255.0F * fabs(unit_direction.y * 255) * h_divider;
	color.z = 64.0F;
    return vec3_to_color(&color);
}

# define BG -1
int		ray_sphere(t_ray_vec3 *r, t_obj *sp, t_hit_rec *rec)
{
	static t_vec3		z_norm = { .x = 0.0, .y = 0.0, .z = -1.0 };
	static t_vec3		unit = { .x = 1.0, .y = 1.0, .z = 1.0 };
	t_vec3				color;
	
    if (hit_sphere(r, sp, rec, T_MIN))
	{
		if (cos_vec3(rec->normal, r->dir) > 0)	// If in same direction, inside obj
			return (sp->color);
		color = mult_vec3(
					add_vec3(
						unit_vec3(sub_vec3(rec->p, z_norm))
						, unit)
				, 127.999F);
        return (vec3_to_color( &color ));
		color = rec->p;
		sub_vec3_self(&color, z_norm);
		unit_vec3_self(&color);
		add_vec3_self(&color, unit);
		mult_vec3_self(&color, 127.999F); // 0.5F * 255
        return (vec3_to_color(&color));
	}

	/* Black background */
	return (BG);
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
			rec.t = 0; 
            pixel_color = ray_sphere(&r, sp, &rec) ;
            pixel_color = (pixel_color == BG ? rt->background : pixel_color);
            // pixel_color = ray_color_sphere(&r, &(sp->center));
            fill_pixel(rt->img, i, j, pixel_color);
        }
    }
	display_default(rt);
	display_fps(rt, start_time);
}