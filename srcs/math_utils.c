#include "minirt.h"

/* Convert degrees to radians */
float	deg_to_rad(float deg)
{
	return (deg * (PI / 180));
}

/* Round a float at a specified precision */
float	roundf_precision(float n, float p)
{
	double	res;

	res = round(n * p);
	return (res / p);
}
