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

/* Function to create a checkerboard pattern */
t_texture uv_checkers(int width, int height, t_color c1, t_color c2)
{
	t_texture res;

	res.width = width;
	res.height = height;
	res.c1 = c1;
	res.c2 = c2;
	return (res);
}
//Returns a struct containing texture data



/* Return color at a given uv coordinate */
t_color uv_pattern_at(t_texture texture, float u, float v)
{
	int	u2 = floor(u * texture.width);
	int	v2 = floor(v * texture.height);

	if ((u2 + v2) % 2 == 0)
		return (texture.c1);
	else
		return (texture.c2);
}






t_color pattern_at(t_vec3 p, t_texture texture, char type)
{
	t_vec2 uv;

	if (type == T_SPH)
		uv = spherical_map(p);
	else if (type == T_PLANE)
		uv = planar_map(p);
	else if (type == T_CYL)
		uv = cylindrical_map(p);
	return (uv_pattern_at(texture, uv.u, uv.v));
}

t_uv uv_at(t_vec3 p, t_texture texture, char type)
{
	t_vec2	uv;
	t_uv	res;
	if (type == T_SPH)
		uv = spherical_map(p);
	else if (type == T_PLANE)
		uv = planar_map(p);
	else if (type == T_CYL)
		uv = cylindrical_map(p);

	res.u = floor((1.0f - uv.u) * texture.width);
	res.v = floor((1.0f - uv.v) * texture.height);
	return (res);
}


t_vec2 planar_map(t_vec3 p)
{
	t_vec2 res;
	double t1;
	double t2;

	res.u = modf(p.x, &t1);
	res.v = modf(p.z, &t2);
	return (res);
}

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
/* Get colour for non-image texture */
t_color pattern_at(t_vec3 p, t_texture texture, char type)
{
	t_vec2 uv;

	if (type == T_SPH)
		uv = spherical_map(p);
	else if (type == T_PLANE)
		uv = planar_map(p);
	else if (type == T_CYL)
		uv = cylindrical_map(p);
	return (uv_pattern_at(texture, uv.u, uv.v));
}


t_color uv_pattern_at_image(t_texture texture, float u, float v)
{
	//1 - value is to invert texture
	int	u2 = floor( (1 - u) * texture.width);

	int	v2 = floor( (1 - v) * texture.height);


	t_color ret = texture.image.pixels[v2][u2];
	return (ret);
}

/* Get colour for image texture */
t_color pattern_at_image(t_vec3 p, t_texture texture, char type)
{
	t_vec2 uv;

	if (type == T_SPH)
		uv = spherical_map(p);
	else if (type == T_PLANE)
		uv = planar_map(p);
	else if (type == T_CYL)
		uv = cylindrical_map(p);
	return (uv_pattern_at_image(texture, uv.u, uv.v));
}

/* Get texture colour for current object */

/* To-do:
	- Properly apply inverse rotation and translation to each object before calculating uv
		- Not sure if this matters for planes, but def matters for cylinder and sphere
		- Rotation does not seem to matter for planes
	- Embed each texture inside object
	- Figure out where to call the uv mapping function from
	- Remove t_vec2 and just use vec3 instead
*/





/* Get colour for image texture */
t_color pattern_at_image(t_vec3 p, t_texture texture, char type)
{
	t_vec2 uv;

	if (type == T_SPH)
		uv = spherical_map(p);
	else if (type == T_PLANE)
		uv = planar_map(p);
	else if (type == T_CYL)
		uv = cylindrical_map(p);
	return (uv_pattern_at_image(texture, uv.u, uv.v));
}

/* Apply texture*/
rec->color = pattern_at_image(sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->earth, T_SPH); //For applying texture to sphere
/* Apply normal */
rec->normal = perturb_normal(rec->normal, normal_image_to_vec3(uv_at(sub_vec3(rec->p, rt->objs[rec->obj_id]->pos), rt->earth_normal, T_SPH), rt->earth_normal.image));