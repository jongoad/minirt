#include "minirt.h"

/* Convert a 3d point to uv coords on a sphere*/
t_vec2 spherical_map(t_vec3 p)
{
	t_vec2 res;

	float theta = atan2(p.x, p.z);
	t_vec3 vec = vec3(p.x, p.y, p.z);
	float radius = length_vec3(vec);
	float phi = acos(p.y / radius);
	float raw_u = theta / (2 * PI);
	res.u = 1 - (raw_u + 0.5f);
	res.v = 1 - (phi / PI);
	return (res);
}

/* Convert a 3D point to UV coords on a plane */
t_vec2 planar_map(t_vec3 p)
{
	t_vec2 res;
	double t1;
	double t2;

	res.u = modf(p.x, &t1);
	res.v = modf(p.z, &t2);
	return (res);
}
/* Convert a 3D point to UV coords on a cylinder */
t_vec2 cylindrical_map(t_vec3 p)
{
	t_vec2	res;
	double t1;

	//compute the azimuthal angle, same as with spherical_map()
	float theta = atan2(p.x, p.z);
	float raw_u = theta / (2 * PI);
	res.u = 1.0f - (raw_u + 0.5f);

	// let v go from 0 to 1 between whole units of y
	res.v = modf(p.y, &t1);


	return (res);
}