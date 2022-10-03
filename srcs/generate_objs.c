#include "minirt.h"

t_obj	*new_sphere(t_vec3 center, float radius, t_vec3 color)
{
	t_obj	*sp;

	sp = ft_xalloc(sizeof(t_obj));
	sp->radius = radius;
	sp->center = center;
	sp->color = color;
	sp->type = T_SPH;
	sp->hit = hit_sphere;
	sp->hit_no_rec = hit_sphere_no_hit_rec;
	return (sp);
}

t_obj	*new_plane(t_vec3 center, t_vec3 normal, t_vec3 color)
{
	t_obj	*plane;

	plane = ft_xalloc(sizeof(t_obj));
	plane->center = center;
	plane->color = color;
	plane->normal = normal;
	plane->type = T_PLANE;
	plane->hit = hit_plane;
	// plane->hit_no_rec = hit_plane_no_hit_rec;
	return (plane);
}
