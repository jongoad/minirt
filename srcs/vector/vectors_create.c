#include "minirt.h"

/* Return a vec3 from component inputs */
t_vec3  vec3(float x, float y, float z)
{
	t_vec3  v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
