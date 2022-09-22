#include "minirt.h"

t_obj	*new_sphere( t_vec3 center, float radius, t_vec3 color )
{
	t_obj	*sp;

	sp = ft_xalloc(sizeof(t_obj));
	sp->radius = radius;
	sp->center = center;
	sp->color = color;
	sp->type = 's';
	sp->hit = hit_sphere;
	sp->hit_no_rec = hit_sphere_no_hit_rec;
	return (sp);
}
