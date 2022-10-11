#include "minirt.h"
#include <time.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

t_vec3	ray_at(t_ray_vec3 *r, float t)
{
	return add_vec3(r->orig, mult_vec3(r->dir, t));
}

bool	hit_plane(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
	float	discriminant;
	float	t;

	discriminant = dot_vec3(o->normal, r->dir);
    if (fabs(discriminant) > T_MIN)
	{
		t = dot_vec3(sub_vec3(o->center, r->orig), o->normal) / discriminant;
		if (t >= T_MIN && t < rec->t)
		{
			rec->t = t;
			rec->hit_anything = true;
			rec->color = o->color;
			rec->normal = o->normal;
			rec->p = ray_at(r, rec->t);
			return (true);
		}
	}
	return false;
}

bool	hit_cylinder_caps(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
	static t_obj	cap1;
	static t_obj	cap2;
	float			tmp;

	tmp = rec->t;
	unit_vec3_self(&(o->normal));
	// cap1.center = add_vec3(o->center, mult_vec3(o->normal, o->height / 2));
	cap1.center = vec3(o->center.x, o->center.y + o->height / 2, o->center.z);
	cap1.normal = o->normal;
	cap1.color = o->color;
	cap2.center = vec3(o->center.x, o->center.y - o->height / 2, o->center.z);
	cap2.normal = negate_vec3(o->normal);
	cap2.color = o->color;
	hit_plane(r, &cap1, rec);
	if (rec->hit_anything && length_vec3(sub_vec3(rec->p, cap1.center)) >= o->radius)
	{
		rec->hit_anything = false;
		rec->t = tmp;
	}
	hit_plane(r, &cap2, rec);
	if (rec->hit_anything && length_vec3(sub_vec3(rec->p, cap2.center)) >= o->radius)
	{
		rec->hit_anything = false;
		rec->t = tmp;
	}
	return (rec->hit_anything);
}

bool	hit_cylinder(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
    t_vec3					oc;
    t_vec3					point;
    t_vec3					color;
	static t_quadratic		q;
	// static t_hit_rec		rec2;

	color = o->color;
	oc = sub_vec3(r->orig, o->center);
	q.a = (r->dir.x * r->dir.x) + (r->dir.z * r->dir.z);
	if (q.a == 0)
		return (false);
	q.half_b = (oc.x * r->dir.x) + (oc.z * r->dir.z);
	q.c = (oc.x * oc.x) + (oc.z * oc.z) - o->radius * o->radius;
	q.discriminant = q.half_b * q.half_b - q.a * q.c;
    if (q.discriminant < 0)
        return false;	
    q.sqrtd = sqrtf(q.discriminant);
    q.root = (-q.half_b - q.sqrtd) / q.a;

	point = ray_at(r, q.root);
	hit_cylinder_caps(r, o, rec);
	// if (q.root < T_MIN || q.root > rec->t || point.y > o->cyl_offset || -point.y > (o->height - o->cyl_offset))
	// 		return false;
	if (q.root < T_MIN || q.root > rec->t || point.y > o->cyl_offset || -point.y > (o->height - o->cyl_offset))
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
		point = ray_at(r, q.root);
		if (q.root < T_MIN || q.root > rec->t || point.y > o->cyl_offset || -point.y > (o->height - o->cyl_offset))
			return false;
		color = color_to_vec3(BLACK);
		rec->inside_surface = true;
	}

	// rec2.hit_anything = false;
	// rec2.t = T_MAX;

	// hit_cylinder_caps(r, o, &rec2);	

	// if (q.root < rec->t && q.root < rec2.t) {
	if (q.root < rec->t) {
		rec->hit_anything = true;
		rec->t = q.root;
		rec->p = point;
		// rec->normal = div_vec3(sub_vec3(rec->p, o->center), o->radius);
		rec->normal = unit_vec3(sub_vec3(rec->p, add_vec3(o->center, vec3(0, rec->p.y - o->center.y, 0))));
		rec->color = color;
		return true;
	}
	// if (rec2.hit_anything)
	// {
	// 	rec->hit_anything = true;
	// 	rec->t = rec2.t;
	// 	rec->p = rec2.p;
	// 	rec->normal = rec2.normal;
	// 	rec->color = color;
	// 	return true;
	// }
	// return hit_cylinder_caps(r, o, rec);
	return false;
}

bool	hit_sphere(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
    t_vec3			oc;
	static t_quadratic		q;

	oc = sub_vec3(r->orig, o->center);
	q.a = dot_vec3(r->dir, r->dir);
	if (q.a == 0)
		return (false);
	q.half_b = dot_vec3(oc, r->dir);
	q.c = dot_vec3(oc, oc) - o->radius * o->radius;
	q.discriminant = q.half_b * q.half_b - q.a * q.c;
    if (q.discriminant < 0)
        return false;	
    q.sqrtd = sqrtf(q.discriminant);
    q.root = (-q.half_b - q.sqrtd) / q.a;
    if (q.root < T_MIN || q.root > T_MAX)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
        if (q.root < T_MIN || q.root > T_MAX)
			return false;
		rec->inside_surface = true;
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

static inline bool	hit_anything(t_data *rt, t_ray_vec3 *pt_to_light, t_hit_rec *rec, t_hit_rec *rec2)
{
	int		i;

	(void) rec2;
	(void) rec;
	i = -1;
	while (++i < rt->nb_objs)
	{
		if (rt->objs[i]->hit(pt_to_light, rt->objs[i], rec2))
		{
			return (true);
		}
	}
	return (false);
}

int	apply_point_lights(t_data *rt, t_hit_rec *rec, int color)
{
	t_vec3		vcolor; 
	t_ray_vec3	pt_to_light;
	t_hit_rec	rec2;
	t_vec3		diff;
	float		t;
	int			j;

	//FIXME: to remove
	j = -1;
	while (++j < rt->nb_lights)
	{
		pt_to_light.orig = rec->p;
		diff = sub_vec3(rt->lights[j]->center, rec->p);
		pt_to_light.dir = diff;

		// To verify objects hits are happening before light hit
		rec2.t = length_vec3(diff);
		unit_vec3_self(&pt_to_light.dir);
		// Test for hard shadows
		if (hit_anything(rt, &pt_to_light, rec, &rec2))
			continue;
		t = cos_vec3(rec->normal, diff);
		if (t < 0.01F)
			continue;
		vcolor = color_to_vec3(color);
		color = vec3_to_color(lerp_vec3(vcolor, rt->lights[j]->color, t * t));
	}
	return color;
}

bool	hit_light(t_ray_vec3 *r, t_obj *l, t_hit_rec *rec)
{	
	// FIXME: the light points now have an object type inside of them to store a plane orthogonal to the ray
	l->normal = r->dir;
	return (hit_plane(r, l, rec));
}

int	apply_light_halos(t_data *rt, t_ray_vec3 *r, t_hit_rec *rec, int color, int x, int y)
{
	t_hit_rec		rec2;
	int				i;
	// int				i_obj;
	float			dist;
	
	(void)rec;
	i = -1;
	while (++i < rt->nb_lights)
	{
		rec2.t = T_MAX;
		rec2.hit_anything = false;
		if (hit_light(r, rt->lights[i], &rec2))
		{
			dist = length_vec3(sub_vec3(rt->lights[i]->center, rec2.p));
			dist += 1.0F;
			dist *= dist;
			(void)x;
			(void)y;
			if (dist * dist < LIGHT_RADIUS
				&& (!rec->hit_anything || (rec->hit_anything && rec2.t < rec->t)))
				color = vec3_to_color(rt->lights[i]->color);
			else if (rec->hit_anything == false || (dist * dist < LIGHT_RADIUS && rec2.t < rec->t))
				color = vec3_to_color(lerp_vec3(color_to_vec3(color), rt->lights[i]->color, 1 / dist));
			// else if (rec->hit_anything == false || (dist * dist < LIGHT_RADIUS && rec2.t < rec->t))
			// 	color = vec3_to_color(lerp_vec3(color_to_vec3(color), rt->lights[i]->color, 1 / dist));
		}
	}
	return color;
}

void	objects_apply_inverse_view_matrix(t_data *rt)
{
	t_obj	*o;
	int		i;

	i = 0;
	while (i < rt->nb_objs)
	{
		o = rt->objs[i];
		o->c_center = o->center;
		o->center = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(o->center, T_POINT), rt->cam.view));
		i++;
	}
}

void	render_scene(t_data *rt, t_obj *sp)
{
    // Render
	t_ray_vec3	r;
	int			pixel_color;
	// float		u;
	// float		v;
	
	// Benchmarking
	float		start_time = (float)clock();

	// Hit Record
	t_hit_rec	rec;

	// To traverse objs array
	int		i_obj;

	// cam_init(rt);
	// cam_calc_view(rt);
	// cam_calc_project(rt);
	// cam_generate_rays(rt);

	// FIXME: might be broken ? question mark
	// objects_apply_inverse_view_matrix(rt);

	r.orig = rt->cam.pos;
    for (int j = 0; j < rt->img->height; ++j) {
        for (int i = 0; i < rt->img->width; ++i) {
            // u = (float)(i) / (rt->img->width - 1);
            // v = (float)(j) / (rt->img->height - 1);
			// r.dir = sub_vec3(add3_vec3(
			// 	rt->cam.low_left,
			// 	mult_vec3(rt->cam.horizontal, u),
			// 	mult_vec3(rt->cam.vertical, v)),
			// 	rt->cam.pos);

			r.dir = rt->cam.rays[j][i];
			// unit_vec3_self(&r.dir);
			// if (j == IMG_H / 2)
			// {
			// 	printf("ray[%d][%d]: (%f, %f, %f)\n", i, j, rt->cam.rays[j][i].x, rt->cam.rays[j][i].y, rt->cam.rays[j][i].z);
			// 	printf("ray[%d][%d]: (%f, %f, %f)\n", i, j, r.dir.x, r.dir.y, r.dir.z);
			// }
			rec.color = color_to_vec3(rt->background);
			rec.t = T_MAX;
			rec.hit_anything = false;

			pixel_color = rt->background;

			i_obj = -1;
			while (++i_obj < rt->nb_objs)
			{
				if (rt->objs[i_obj]->type == T_LIGHT)
					continue ;
				if (rt->objs[i_obj]->hit(&r, rt->objs[i_obj], &rec))
				{
					rec.obj_id = i_obj;
				}
				// if (rt->objs[i_obj]->type == T_CYL && hit_cylinder_caps(&r, rt->objs[i_obj], &rec))
				// 	rec.obj_id = i_obj;
			}
			
			// if (rec.hit_anything)
            // 	pixel_color = apply_point_lights(rt, &rec, vec3_to_color(rec.color));
			if (rec.hit_anything)
            	pixel_color = vec3_to_color(rec.color);
			
			// if (rt->apply_light_halos == true)
			// 	pixel_color = apply_light_halos(rt, &r, &rec, pixel_color, i, j);
			
            fill_pixel(rt->img, i, j, pixel_color);
        }
    }
	(void)sp;

	display_default(rt);
	display_fps(rt, start_time);
}
