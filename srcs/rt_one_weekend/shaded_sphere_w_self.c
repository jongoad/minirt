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
	/* First cap */
	cap1.fwd = o->fwd;
	cap1.pos = add_vec3(o->pos, mult_vec3(cap1.fwd, o->height / 2));
	cap1.color = o->color;

	/* Second cap */
	cap2.fwd = negate_vec3(o->fwd);
	cap2.pos = add_vec3(o->pos, mult_vec3(cap2.fwd, o->height / 2));
	cap2.color = o->color;

	/* Init temp hit record */
	rec2.t = T_MAX;
	rec2.hit_anything = false;
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
	return (hit_anything); 
}

int	sign(float f)
{
	if (f < 0)
		return (-1);
	else if (f == 0)
		return (0);
	return (1);
}

bool	hit_cylinder(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
	// const t_vec3	oc = sub_vec3(r->orig, o->pos);
	// const float		card = dot_vec3(o->ccap, r->dir);
	// const float		caoc = dot_vec3(o->ccap, oc);
	// const float		a = o->mag_ccap - card * card;
	// const float		b = o->mag_ccap * dot_vec3(oc, r->dir) - caoc * card;
	// float			h = b * b - a * (o->mag_ccap * dot_vec3(oc, oc) - caoc * caoc - o->radius * o->radius * o->mag_ccap);
	// float			y;
	// // float			t;

	// if (h < 0.0)
	// 	return (false);
	// h = sqrtf(h);
	// rec->t = (-b - h) / a;
	// y = caoc + rec->t * card;
	
	// // normal = (oc + (dir * t) - (ccap * y / mag_ccap)) / radius
	
	// if (y > 0.0 && y < o->mag_ccap)
	// 	rec->normal = (o->fwd, o->right);
	// 	// rec->normal = unit_vec3(mult_vec3(add_vec3(oc, sub_vec3(mult_vec3(r->dir, rec->t), mult_vec3(\
	// 	// mult_vec3(o->ccap, y), 1.0 / o->mag_ccap))), 1.0 / o->radius));
	// else
	// {
	// 	rec->t = (o->mag_ccap * !(y < 0.0) - caoc) / card;
	// 	if (fabs(b + a * rec->t) >= h)
	// 		return (false);
	// 	// rec->normal = unit_vec3(mult_vec3(mult_vec3(o->ccap, sign(y)), \
	// 	// 	1.0 / o->mag_ccap));
	// 	rec->normal = o->fwd;
	// }
	// rec->p = add_vec3(r->orig, mult_vec3(r->dir, rec->t));
	// rec->hit_anything = true;
	// rec->color = o->color;
	// return (true);



    t_vec3					oc;
    t_ray_vec3				lr;
    t_vec3					point;
    t_vec3					color;
	static t_quadratic		q;

	lr.dir = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(r->dir, T_VEC), o->w_to_l));
	lr.orig = sub_vec3(o->pos, r->orig);
	lr.orig = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(r->orig, T_POINT), o->w_to_l));

	// return (hit_cylinder_caps(&lr, o, rec));
	color = o->color;
	oc = sub_vec3(lr.orig, o->pos);
	q.a = (lr.dir.x * lr.dir.x) + (lr.dir.z * lr.dir.z);
	if (q.a == 0)
		return (false);
	q.half_b = (oc.x * lr.dir.x) + (oc.z * lr.dir.z);
	q.c = (oc.x * oc.x) + (oc.z * oc.z) - o->radius * o->radius;
	q.discriminant = q.half_b * q.half_b - q.a * q.c;
    if (q.discriminant < 0)
        return false;
    q.sqrtd = sqrtf(q.discriminant);
    q.root = (-q.half_b - q.sqrtd) / q.a;

	point = ray_at(&lr, q.root);
	if (q.root < T_MIN || q.root > rec->t || fabs(point.y - o->pos.y) > o->height / 2)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
		point = ray_at(&lr, q.root);
		// if (hit_cylinder_caps(r, o, rec))
		// 	return (true);

		hit_cylinder_caps(r, o, rec);
		if (q.root < T_MIN || q.root > rec->t || fabs(point.y - o->pos.y) > o->height / 2)
			return false;
		color = color_to_vec3(BLACK);
		rec->inside_surface = true;
	}

	if (q.root < rec->t) {
		rec->hit_anything = true;
		rec->t = q.root;
		rec->p = ray_at(r, rec->t);
		// rec->p = vec4_to_vec3(mat_mult_vec4(vec3_to_vec4(point, T_POINT), o->l_to_w));
		// rec->normal = div_vec3(sub_vec3(rec->p, o->pos), o->radius);
		rec->normal = unit_vec3(sub_vec3(rec->p, add_vec3(o->pos, vec3(0, rec->p.y - o->pos.y, 0))));
		rec->color = color;
		return true;
	}
	return false;
}
