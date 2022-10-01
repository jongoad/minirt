#include "../includes/minirt.h"

/* Allocate a block of memory and set all bytes to 0 */
void	*ft_xalloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	if (!mem_space)
	{
		write(STDERR_FILENO, "Malloc Error\n", 13);
		exit(EXIT_FAILURE);
	}
	ft_bzero(mem_space, size);
	return (mem_space);
}

t_data* get_data(void)
{
	static t_data *rt = NULL;
	if (!rt)
		rt = ft_xalloc(sizeof(t_data));
	return (rt);
}

void	matrix_test(void)
{
	float **mat;
	t_point a;
	t_point b;

	a.x = 0;
	a.y = 0;
	a.z = 0;
	a.w = 1;

	b.x = 0;
	b.y = 10;
	b.z = 0;
	b.w = 1;

	t_point t;

	t.x = 5;
	t.y = 5;
	t.z = -3;
	t.w = 1;
	
	mat = mat_trans(t);

	mat_mult_vec4(&a, mat);
	mat_mult_vec4(&b, mat);

	printf("Point A:\n");
	printf("x: %f\ny: %f\nz: %f\nw: %f\n\n", a.x, a.y, a.z, a.w);

	printf("PointB:\n");
	printf("x: %f\ny: %f\nz: %f\nw: %f\n\n", b.x, b.y, b.z, b.w);

	
}


int	main(int argc, char **argv)
{

	t_data *rt;

	rt = get_data();

	printf("Argc: %i\n", argc);
	printf("Path: %s\n", argv[1]);
	if (argc != 2)
		printf("%s\n", BAD_ARG_ERR);
	if (!parse(rt, argv[1]))
		printf("Parse error\n");
	else
		printf("Parse successful\n");

	matrix_test();
}



