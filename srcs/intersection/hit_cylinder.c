#include "minirt.h"

static bool	cylinder_quadratic(t_ray *r, t_obj *o, t_quadratic *q)
{
	q->oc = sub_vec3(r->orig, o->pos);
	q->dir_dot_fwd = dot_vec3(r->dir, o->fwd);
	q->oc_dot_fwd = dot_vec3(q->oc, o->fwd);

	q->a = dot_vec3(r->dir, r->dir) - q->dir_dot_fwd * q->dir_dot_fwd;
	q->half_b = dot_vec3(r->dir, q->oc) - q->dir_dot_fwd * q->oc_dot_fwd;
	q->c = dot_vec3(q->oc, q->oc) -
		q->oc_dot_fwd * q->oc_dot_fwd - o->radius * o->radius;

	q->discriminant = q->half_b * q->half_b - q->a * q->c;
	if (q->discriminant < 0)
		return (false);
	q->sqrtd = sqrtf(q->discriminant);
	q->root = (-q->half_b - q->sqrtd) / q->a;
	return (true);
}

/** Formula for body intersection found at 
 *  https://hugi.scene.org/online/hugi24/ \
 * 	coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
**/
bool	hit_cylinder_body(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	static t_quadratic		q;
	double					dist;

	if (cylinder_quadratic(r, o, &q) == false)
		return (false);
	dist = q.dir_dot_fwd * q.root + q.oc_dot_fwd;
	if (q.root < T_MIN || q.root > rec->t || fabs(dist) > o->half_height)
	{
		q.root = (-q.half_b + q.sqrtd) / q.a;
		dist = q.dir_dot_fwd * q.root + q.oc_dot_fwd;
		if (q.root < T_MIN || q.root >= rec->t || fabs(dist) > o->half_height)
			return (false);
		rec->inside_surface = true;
	}
	rec->hit_anything = true;
	rec->t = q.root;
	rec->p = ray_at(r, rec->t);
	rec->color = o->clr;
	rec->normal = unit_vec3(
			sub_vec3(
				sub_vec3(rec->p, o->pos),
				mult_vec3(o->fwd, dist)));
	return (true);
}

bool	hit_cylinder(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	bool	hit;

	hit = false;
	if (hit_caps(r, o, rec))
		hit = true;
	if (hit_cylinder_body(r, o, rec))
		hit = true;
	return (hit);
}
