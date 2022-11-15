#include "minirt.h"

/* Adds two vectors */
t_vec3  add_vec3(t_vec3 a, t_vec3 b)
{
	return vec3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z);
}

/* Gives dot product between two vectors */
double   dot_vec3(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x)
		+ (a.y * b.y)
		+ (a.z * b.z);
}

/* Substracts a vector from another */
t_vec3  sub_vec3(t_vec3 a, t_vec3 b)
{
	return vec3(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z);
}

/* Cross product between two vectors */
t_vec3  cross_vec3(t_vec3 a, t_vec3 b)
{
	return vec3(
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x));
}

/* Linear interpolation between two vectors Factor should be between 0.0f-1.0f */
t_vec3  lerp_vec3(t_vec3 a, t_vec3 b, float factor)
{
	t_vec3  diff;
	
	if (factor <= 0.0F)
	{
		return vec3(a.x, a.y, a.z);
	}
	else if (factor > 1.0F)
	{
		factor = 1.0F;
	}
	diff = sub_vec3(b, a);
	return add_vec3(a, mult_vec3(diff, factor));
}
