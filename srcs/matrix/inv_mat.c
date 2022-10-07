#include "minirt.h"

/* Determinant calculation function */
double determinant(t_mat4 a, double k)
{
	t_i i;
	double s;
	double det;
	t_mat4 b;
	int m;
	int n;

	s = 1;
	det = 0;
	if (k == 1)
		return (a.m[0][0]);
	else
	{
		det = 0;
		i.i = 0;
		while (i.i < k)
		{
			m = 0;
			n = 0;
			i.j = 0;
			while (i.j < k)
			{
				i.k = 0;
				while (i.k < k)
				{
					b.m[i.j][i.k] = 0;
					if (i.j != 0 && i.k != i.i)
					{
						b.m[m][n] = a.m[i.j][i.k];
						if (n < (k - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
					i.k++;
				}
				i.j++;
			}
			det = det + s * (a.m[0][i.i] * determinant(b, k - 1));
			s = -1 * s;
			i.i++;
		}
	}
    return (det);
}

/* Cofactor calculation function */
t_mat4	mat_inv(t_mat4 a, double f)
{
	t_i		i;
	t_mat4	b;
	t_mat4	fac;
	int		m;
	int		n;

	//Need to fix return type so we can return (null) on error 
	if (determinant(a, 4) == 0)
	{
		printf("Since the determinant is zerp (0), therefor inverse is not possible.");
		return (b);
	}
	i.i = 0;
	while (i.i < f)
	{
		i.j = 0;
		while (i.j < f)
		{
			m = 0;
			n = 0;
			i.k = 0;
			while (i.k < f)
			{
				i.z = 0;
				while(i.z < f)
				{
					if (i.k != i.i && i.z != i.j)
					{
						b.m[m][n] = a.m[i.k][i.z];
						if (n < (f - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
					i.z++;
				}
				i.k++;
			}
			fac.m[i.i][i.j] = pow(-1, i.i + i.j) * determinant(b, f - 1);
			i.j++;
		}
		i.i++;
	}
  	return (transpose(a, fac, f));
}
 
/* Function to find transpose of a matrix */
t_mat4	transpose(t_mat4 a, t_mat4 fac, double r)
{
	t_i i;
	t_mat4 b;
	t_mat4 inv;
	double d;

	i.i = 0;
	while (i.i < r)
	{
		i.j = 0;
		while (i.j < r)
		{
			b.m[i.i][i.j] = fac.m[i.j][i.i];
			i.j++;
		}
		i.i++;
	}
	d = determinant(a, r);
	i.i = 0;
	while (i.i < r)
	{
		i.j = 0;
		while (i.j < r)
		{
			inv.m[i.i][i.j] = b.m[i.i][i.j] / d;
			i.j++;
		}
		i.i++;
	}
	return (inv);
}