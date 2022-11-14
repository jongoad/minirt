#include "minirt.h"

bool	hit_caps(t_ray *r, t_obj *o, t_hit_rec *rec)
{
	static t_obj		cap1;
	static t_obj		cap2;
	bool				hit;

	cap1.fwd = o->fwd;
	cap1.pos = add_vec3(o->pos, mult_vec3(cap1.fwd, o->half_height));
	cap1.radius = o->radius;
	cap1.clr = o->clr;

	cap2.fwd = negate_vec3(o->fwd);
	cap2.pos = add_vec3(o->pos, mult_vec3(cap2.fwd, o->half_height));
	cap2.radius = o->radius;
	cap2.clr = o->clr;

	hit = false;
	if (hit_disk(r, &cap1, rec))
		hit = true;
	if (hit_disk(r, &cap2, rec))
		hit = true;
	return (hit);
}
