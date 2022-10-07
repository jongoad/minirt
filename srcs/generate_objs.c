#include "minirt.h"

t_obj	*new_sphere(t_vec3 center, float radius, t_vec3 color)
{
	t_obj	*obj;

	obj = ft_xalloc(sizeof(t_obj));
	obj->radius = radius;
	obj->center = center;
	obj->color = color;
	obj->type = T_SPH;
	obj->hit = hit_sphere;
	return (obj);
}

t_obj	*new_plane(t_vec3 center, t_vec3 normal, t_vec3 color)
{
	t_obj	*obj;

	obj = ft_xalloc(sizeof(t_obj));
	obj->center = center;
	obj->color = color;
	obj->normal = normal;
	obj->type = T_PLANE;
	obj->hit = hit_plane;
	return (obj);
}

t_obj	*new_cylinder(t_vec3 center, t_vec3 normal, float diameter, float height, t_vec3 color)
{
	t_obj	*obj;

	obj = ft_xalloc(sizeof(t_obj));
	obj->center = center;
	obj->color = color;
	obj->normal = normal;
	obj->height = height;
	obj->radius = diameter / 2.0F;
	obj->type = T_CYL;
	obj->hit = hit_cylinder;
	obj->cyl_offset = 0.0F;
	return (obj);
}
