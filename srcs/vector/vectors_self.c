#include "minirt.h"

/* Directly add a vec3's components to the calling vec3 */
void	add_vec3_self(t_vec3 *a, t_vec3 b)
{
		a->x += b.x;
		a->y += b.y;
		a->z += b.z;
}

/* Directly adds 2 vec3's components to the calling vec3 */
void	add3_vec3_self(t_vec3 *a, t_vec3 b, t_vec3 c)
{
		a->x += b.x + c.x;
		a->y += b.y + c.y;
		a->z += b.z + c.z;
}

/* Directly subs a vec3's components from the calling vec3 */
void	sub_vec3_self(t_vec3 *a, t_vec3 b)
{
		a->x -= b.x;
		a->y -= b.y;
		a->z -= b.z;
}

/* Directly multiplies a vec3's components by the calling vec3's components, and attributes them to the calling vec3 */
void	mult_vec3_vec3_self(t_vec3 *a, t_vec3 b)
{
		a->x *= b.x;
		a->y *= b.y;
		a->z *= b.z;
}

/* Directly multiplies a vec3's components by a scalar */
void	mult_vec3_self(t_vec3 *v, double b)
{
		v->x *= b;
		v->y *= b;
		v->z *= b;
}

/* Directly divides a vec3's components by a scalar */
void	div_vec3_self(t_vec3 *v, double b)
{
	return mult_vec3_self(v, 1.0f / b);
}

/* Directly transforms calling vector into unit vector (length == 1) */
void	unit_vec3_self(t_vec3 *v)
{
	double is;

	is = 1 / sqrtf(
		v->x * v->x
		+ v->y * v->y
		+ v->z * v->z);
	return mult_vec3_self(v, is);
}

/* Directly transforms calling vector into its cross product with second vector */
void	cross_vec3_self(t_vec3 *a, t_vec3 b)
{
	a->x = (a->y * b.z) - (a->z * b.y);
	a->y = (a->z * b.x) - (a->x * b.z);
	a->z = (a->x * b.y) - (a->y * b.x);
}

/* Directly negates all components of the calling vector */
void	negate_vec3_self(t_vec3 *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}
