#include "minirt.h"
#include <stdio.h>
#include <math.h>


/******************************************************/
/* Convert orientation vector to full matrix */
// void	*ft_xalloc(size_t size)
// {
// 	void	*mem_space;

// 	mem_space = malloc(size);
// 	if (!mem_space)
// 	{
// 		write(STDERR_FILENO, "Malloc Error\n", 13);
// 		exit (EXIT_FAILURE);
// 	}
// 	return (mem_space);
// }

// t_vec3  vec3(double x, double y, double z)
// {
//     t_vec3  v;

//     v.x = x;
//     v.y = y;
//     v.z = z;
//     return (v);
// }

// t_vec3  mult_vec3(t_vec3 v, double b)
// {
//     return vec3(
//         v.x * b,
//         v.y * b,
//         v.z * b);
// }

// t_vec3  cross_vec3(t_vec3 a, t_vec3 b)
// {
//     return vec3(
//         (a.y * b.z) - (a.z * b.y),
//         (a.z * b.x) - (a.x * b.z),
//         (a.x * b.y) - (a.y * b.x));
// }

// t_vec3  unit_vec3(t_vec3 v)
// {
//     double is;

//     is = 1 / sqrtf(
//         (v.x) * (v.x)
//         + (v.y) * (v.y)
//         + (v.z) * (v.z));
//     return mult_vec3(v, is);
// }

// t_mat4	orient_to_rot(t_vec3 direct)
// {
// 	t_mat4 m;

// 	t_vec3 tmp_up;
// 	tmp_up.x = 0;
// 	tmp_up.y = 1;
// 	tmp_up.z = 0;

// 	t_vec3	x = cross_vec3(direct, tmp_up);
// 	x = unit_vec3(x);

// 	t_vec3	y = cross_vec3(direct, x);
// 	y = unit_vec3(y);

// 	m.m[0][0] = x.x;
// 	m.m[1][0] = y.x;
// 	m.m[2][0] = direct.x;
// 	m.m[3][0] = 0;

// 	m.m[0][1] = x.y;
// 	m.m[1][1] = y.y;
// 	m.m[2][1] = direct.y;
// 	m.m[3][2] = 0;

// 	m.m[0][2] = x.z;
// 	m.m[1][2] = y.z;
// 	m.m[2][2] = direct.z;
// 	m.m[3][2] = 0;
	
// 	return (m);
// }

// /**************************************************************/



// int main()
// {

// 	t_i i;
// 	t_vec3 orient;

// 	orient.x = 1;
// 	orient.y = 0;
// 	orient.z = 1;

// 	t_mat4	a;


// 	a.m[0][0] = 1;
// 	a.m[1][0] = 0;
// 	a.m[2][0] = 0;
// 	a.m[3][0] = 0;

// 	a.m[0][1] = 0;
// 	a.m[1][1] = 1;
// 	a.m[2][1] = 0;
// 	a.m[3][1] = 0;

// 	a.m[0][2] = 0;
// 	a.m[1][2] = 0;
// 	a.m[2][2] = -1;
// 	a.m[3][2] = 0;

// 	a.m[0][3] = 2;
// 	a.m[1][3] = 2;
// 	a.m[2][3] = 2;
// 	a.m[3][3] = 1;

// 	// printf("Printing constructed matrix for object\n\n");

// 	printf("Printing before inverse\n\n");
// 	i.y = 0;
// 	while (i.y < 4)
// 	{
// 		i.x = 0;
// 		while (i.x < 4)
// 		{
// 			printf("\t%f", a.m[i.y][i.x]);
// 			i.x++;
// 		}
// 		printf("\n");
// 		i.y++;
// 	}

// 	t_mat4 inv;
	
// 	inv = mat_inv(a, 4);

// 	printf("\nPrinting after inverse\n\n");
// 	i.y = 0;
// 	while (i.y < 4)
// 	{
// 		i.x = 0;
// 		while (i.x < 4)
// 		{
// 			printf("\t%f", inv.m[i.y][i.x]);
// 			i.x++;
// 		}
// 		printf("\n");
// 		i.y++;
// 	}

// 	t_mat4 res;

// 	res = mat_mult_mat(a, inv);

// 	printf("\nOriginal matrix multiplied with inverse\n\n");
// 	i.y = 0;
// 	while (i.y < 4)
// 	{
// 		i.x = 0;
// 		while (i.x < 4)
// 		{
// 			printf("\t%f", res.m[i.y][i.x]);
// 			i.x++;
// 		}
// 		printf("\n");
// 		i.y++;
// 	}

// }

// //https://www.gamedev.net/forums/topic/707632-rotate-object-in-world-space-raytracing/




