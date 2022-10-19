#include "minirt.h"

/* Create three axis vectors from a single direction vector */
t_mat4	orient_to_rot(t_vec3 direct)
{
	t_mat4 m;

	t_vec3 tmp_up;
	tmp_up.x = 0;
	tmp_up.y = 1;
	tmp_up.z = 0;

	t_vec3	x = cross_vec3(direct, tmp_up);
	x = unit_vec3(x);

	t_vec3	y = cross_vec3(direct, x);
	y = unit_vec3(y);

	m.m[0][0] = x.x;
	m.m[1][0] = y.x;
	m.m[2][0] = direct.x;
	m.m[3][0] = 0;

	m.m[0][1] = x.y;
	m.m[1][1] = y.y;
	m.m[2][1] = direct.y;
	m.m[3][2] = 0;

	m.m[0][2] = x.z;
	m.m[1][2] = y.z;
	m.m[2][2] = direct.z;
	m.m[3][2] = 0;
	
	return (m);
}

/* Multiply two matrices together */
t_mat4	mat_mult_mat(t_mat4 m1, t_mat4 m2)
{
	t_mat4	m_res;
	t_i		i;

	mat_id(&m_res);
	i.y = 0;
	while (i.y < 4)
	{
		i.x = 0;
		while (i.x < 4)
		{
			m_res.m[i.y][i.x] = (m1.m[i.y][0] * m2.m[0][i.x]) + 
							  (m1.m[i.y][1] * m2.m[1][i.x]) +
						      (m1.m[i.y][2] * m2.m[2][i.x]) +
						      (m1.m[i.y][3] * m2.m[3][i.x]);
			i.x++;
		}
		i.y++;
	}
	return (m_res);
}

/* Multiply a vector by a matrix */
t_vec4	mat_mult_vec4(t_vec4 v, t_mat4 m)
{
	t_vec4	res;

	res.x = (v.x * m.m[0][0]) + (v.y * m.m[0][1]) + (v.z * m.m[0][2]) + (v.w * m.m[0][3]);
	res.y = (v.x * m.m[1][0]) + (v.y * m.m[1][1]) + (v.z * m.m[1][2]) + (v.w * m.m[1][3]);
	res.z = (v.x * m.m[2][0]) + (v.y * m.m[2][1]) + (v.z * m.m[2][2]) + (v.w * m.m[2][3]);
	res.w = (v.x * m.m[3][0]) + (v.y * m.m[3][1]) + (v.z * m.m[3][2]) + (v.w * m.m[3][3]);
	return (res);
}

/* Build a mat4 from four component vec4 */
t_mat4	mat4(t_vec4 a, t_vec4 b, t_vec4 c, t_vec4 d)
{
	t_mat4 res;

	res.m[0][0] = a.x;
	res.m[1][0] = a.y;
	res.m[2][0] = a.z;
	res.m[3][0] = a.w;

	res.m[0][1] = b.x;
	res.m[1][1] = b.y;
	res.m[2][1] = b.z;
	res.m[3][1] = b.w;

	res.m[0][2] = c.x;
	res.m[1][2] = c.y;
	res.m[2][2] = c.z;
	res.m[3][2] = c.w;

	res.m[0][3] = d.x;
	res.m[1][3] = d.y;
	res.m[2][3] = d.z;
	res.m[3][3] = d.w;

	return (res);
}

float	deg_to_rad(float deg)
{
	return (deg * (PI / 180));
}