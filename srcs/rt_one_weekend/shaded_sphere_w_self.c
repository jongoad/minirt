#include "minirt.h"
#include <time.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

bool	hit_sphere(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
    t_vec3			oc;
	static t_quadratic		q;

	oc = sub_vec3(r->orig, o->pos);
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
		rec->normal = div_vec3(sub_vec3(rec->p, o->pos), o->radius);
		rec->color = o->color;
    	return true;
	}
	return false;
}

bool	hit_plane(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
	float	discriminant;
	float	t;

	discriminant = dot_vec3(o->fwd, r->dir);
    if (fabs(discriminant) > T_MIN)
	{
		t = dot_vec3(sub_vec3(o->pos, r->orig), o->fwd) / discriminant;
		if (t >= T_MIN && t < rec->t)
		{
			rec->t = t;
			rec->hit_anything = true;
			rec->color = o->color;
			rec->normal = o->fwd;
			rec->p = ray_at(r, rec->t);
			return (true);
		}
	}
	return false;
}

bool	hit_cylinder_caps(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
	static t_obj		cap1;
	static t_obj		cap2;
	static t_hit_rec	rec2;
	bool				hit_anything;

	hit_anything = false;
	unit_vec3_self(&(o->fwd));
	// cap1.pos = add_vec3(o->pos, mult_vec3(o->normal, o->height / 2));
	cap1.fwd = o->fwd;
	cap1.pos = add_vec3(o->pos, mult_vec3(cap1.fwd, o->height / 2));
	cap1.color = o->color;
	// cap2.pos = vec3(o->pos.x, o->pos.y - o->height / 2, o->pos.z);
	cap2.fwd = negate_vec3(o->fwd);
	cap2.pos = add_vec3(o->pos, mult_vec3(cap2.fwd, o->height / 2));
	cap2.color = o->color;
	rec2.t = T_MAX;
	rec2.hit_anything = false;
	rec2.obj_id = 888;
	if (hit_plane(r, &cap1, &rec2) && length_vec3(sub_vec3(rec2.p, cap1.pos)) <= o->radius && rec2.t < rec->t)
	{
		hit_anything = true;
		*rec = rec2;
	}
	if (hit_plane(r, &cap2, &rec2) && length_vec3(sub_vec3(rec2.p, cap2.pos)) <= o->radius && rec2.t < rec->t)
	{
		hit_anything = true;
		*rec = rec2;
	}
	// {
	// 	if()
	// 		*rec = rec2;
	// 	else
	// 		rec2.hit_anything = false;
	// }
	// if (hit_plane(r, &cap2, &rec2))
	// {
	// 	if(length_vec3(sub_vec3(rec2.p, cap2.pos)) <= o->radius && rec2.t < rec->t)
	// 		*rec = rec2;
	// 	else 
	// 		rec2.hit_anything = false;
	// }
	// if (rec->hit_anything && length_vec3(sub_vec3(rec->p, cap2.pos)) >= o->radius)
	// {
	// 	rec->hit_anything = false;
	// 	rec->t = tmp;
	// }
	return (hit_anything); 
}

bool	hit_cylinder(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
    t_vec3					oc;
    t_vec3					local_ray;
    t_vec3					point;
    t_vec3					color;
	static t_quadratic		q;
	// static t_hit_rec		rec2;

	local_ray = unit_vec3(vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(r->dir, T_VEC), o->w_to_l)));

	color = o->color;
	oc = sub_vec3(r->orig, o->pos);
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
	// hit_cylinder_caps(r, o, rec);
	if (q.root < T_MIN || q.root > rec->t || fabs(point.y - o->pos.y) > o->height / 2)
	{
		return (hit_cylinder_caps(r, o, rec));
        q.root = (-q.half_b + q.sqrtd) / q.a;
		point = ray_at(r, q.root);
		if (q.root < T_MIN || q.root > rec->t || fabs(point.y - o->pos.y) > o->height / 2)
			return false;
		color = color_to_vec3(BLACK);
		rec->inside_surface = true;
	}
	// if (hit_cylinder_caps(r, o, rec))
	// 	color = o->color;

	// rec2.hit_anything = false;
	// rec2.t = T_MAX;

	// hit_cylinder_caps(r, o, &rec2);	

	// if (q.root < rec->t && q.root < rec2.t) {
	if (q.root < rec->t) {
		rec->hit_anything = true;
		rec->t = q.root;
		rec->p = point;
		// rec->normal = div_vec3(sub_vec3(rec->p, o->pos), o->radius);
		rec->normal = unit_vec3(sub_vec3(rec->p, add_vec3(o->pos, vec3(0, rec->p.y - o->pos.y, 0))));
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
