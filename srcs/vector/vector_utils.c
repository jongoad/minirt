#include "minirt.h"

/* Convert a vec3 to a vec4 */
t_vec4	vec3_to_vec4(t_vec3 input, char type)
{
	t_vec4 res;

	res.x = input.x;
	res.y = input.y;
	res.z = input.z;

	if (type == 'v')
		res.w = 0;
	else if (type == 'p')
		res.w = 1;
	
	return (res);
}

/* Convert a vec4 to a vec3 */
t_vec3	vec4_to_vec3(t_vec4 input)
{
	t_vec3 res;

	res.x = input.x;
	res.y = input.y;
	res.z = input.z;

	return (res);
}
