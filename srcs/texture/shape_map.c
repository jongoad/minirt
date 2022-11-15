#include "minirt.h"

/* Convert a 3d point to uv coords on a sphere*/
t_vec2	spherical_map(t_vec3 p)
{
	t_vec2	res;
	float	theta;
	float	radius;
	float	phi;
	float	raw_u;

	theta = atan2(p.x, p.z);
	radius = length_vec3(vec3(p.x, p.y, p.z));
	phi = acos(p.y / radius);
	raw_u = theta / (2 * PI);
	res.u = 1 - (raw_u + 0.5f);
	res.v = 1 - (phi / PI);
	return (res);
}

/* Convert a 3D point to UV coords for a plane */
t_vec2	planar_map(t_vec3 p)
{
	t_vec2	res;
	double	t1;
	double	t2;

	res.u = modf(p.x, &t1);
	res.v = modf(p.z, &t2);
	return (res);
}

/* Convert a 3D point to UV coords for a cylinder */
t_vec2	cylindrical_map(t_vec3 p)
{
	t_vec2	res;
	double	t1;
	float	theta;
	float	raw_u;

	theta = atan2(p.x, p.z);
	raw_u = theta / (2 * PI);
	res.u = 1.0f - (raw_u + 0.5f);
	res.v = modf(p.y, &t1);
	return (res);
}
