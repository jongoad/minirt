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
		rec->color = o->clr;
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
			rec->color = o->clr;
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
	cap1.clr = o->clr;

	/* Second cap */
	cap2.fwd = negate_vec3(o->fwd);
	cap2.pos = add_vec3(o->pos, mult_vec3(cap2.fwd, o->height / 2));
	cap2.clr = o->clr;

	/* Init temp hit record */
	rec2 = *rec;
	rec2.t = T_MAX;
	rec2.hit_anything = false;
	if (hit_plane(r, &cap1, &rec2) && rec2.t < rec->t && length_vec3(sub_vec3(rec2.p, cap1.pos)) <= o->radius)
	{
		hit_anything = true;
		*rec = rec2;
	}
	if (hit_plane(r, &cap2, &rec2) && rec2.t < rec->t && length_vec3(sub_vec3(rec2.p, cap2.pos)) <= o->radius)
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


/** Formula for body intersection found at 
 *  https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
**/ 
bool	hit_cylinder_body(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
    t_vec3					oc;
	static t_quadratic		q;
	double					dist;
	double					dir_x_fwd;
	double					oc_x_fwd;

	oc = sub_vec3(r->orig, o->pos);
	dir_x_fwd = dot_vec3(r->dir, o->fwd);
	oc_x_fwd = dot_vec3(oc, o->fwd);

	q.a = dot_vec3(r->dir, r->dir) - dir_x_fwd * dir_x_fwd;
	q.half_b = dot_vec3(r->dir, oc) - dir_x_fwd * oc_x_fwd;
	q.c = dot_vec3(oc, oc) - oc_x_fwd * oc_x_fwd - o->radius * o->radius;

	q.discriminant = q.half_b * q.half_b - q.a * q.c;
    if (q.discriminant < 0)
        return false;
    q.sqrtd = sqrtf(q.discriminant);
    q.root = (-q.half_b - q.sqrtd) / q.a;

	dist = dir_x_fwd * q.root + oc_x_fwd;

	if (q.root < T_MIN || q.root > rec->t || fabs(dist) > o->height / 2)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
		dist = dir_x_fwd * q.root + oc_x_fwd;
		if (q.root < T_MIN || q.root > rec->t || fabs(dist) > o->height / 2)
			return false;
		rec->inside_surface = true;
	}

	if (q.root < rec->t) {
		rec->hit_anything = true;
		rec->t = q.root;
		rec->p = ray_at(r, rec->t);
		rec->color = o->clr;
		rec->normal = unit_vec3(sub_vec3(sub_vec3(rec->p, o->pos), mult_vec3(o->fwd, dist)));
		return true;
	}
	return false;
}

bool	hit_cylinder(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
	bool	hit;
	
	hit = false;
	if (hit_cylinder_caps(r, o, rec))
		hit = true;
	if (hit_cylinder_body(r, o, rec))
		hit = true;
	return (hit);
}


/** Formula for body intersection found at 
 *  https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
**/ 
bool	hit_cone(t_ray_vec3 *r, t_obj *o, t_hit_rec *rec)
{
    t_vec3					oc;
	static t_quadratic		q;
	double					dist;
	double					dir_x_fwd;
	double					oc_x_fwd;
	double					half_tan;
	double					wtf;	//	represents 1 + half_tan^2

	half_tan = tanf(PI / 8);

	oc = sub_vec3(r->orig, o->pos);
	dir_x_fwd = dot_vec3(r->dir, o->fwd);
	oc_x_fwd = dot_vec3(oc, o->fwd);
	wtf = 1 + half_tan * half_tan;

	q.a = dot_vec3(r->dir, r->dir) - wtf * dir_x_fwd * dir_x_fwd;
	q.half_b = dot_vec3(r->dir, oc) - wtf * dir_x_fwd * oc_x_fwd;
	q.c = dot_vec3(oc, oc) - wtf * oc_x_fwd * oc_x_fwd;

	q.discriminant = q.half_b * q.half_b - q.a * q.c;
    if (q.discriminant < 0)
        return false;
    q.sqrtd = sqrtf(q.discriminant);
    q.root = (-q.half_b - q.sqrtd) / q.a;

	dist = dir_x_fwd * q.root + oc_x_fwd;

	if (q.root < T_MIN || q.root > rec->t || fabs(dist) > o->height / 2)
	{
        q.root = (-q.half_b + q.sqrtd) / q.a;
		dist = dir_x_fwd * q.root + oc_x_fwd;
		if (q.root < T_MIN || q.root > rec->t || fabs(dist) > o->height / 2)
			return false;
		rec->inside_surface = true;
	}

	if (q.root < rec->t) {
		rec->hit_anything = true;
		rec->t = q.root;
		rec->p = ray_at(r, rec->t);
		rec->color = o->clr;
		rec->normal = unit_vec3(sub_vec3(sub_vec3(rec->p, o->pos), mult_vec3(o->fwd, dist)));
		return true;
	}
	return false;
}
