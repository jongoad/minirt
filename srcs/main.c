#include "minirt.h"
#include "hooks.h"

void test_invsqrt();

int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err("Error: minirt only accepts a single input\n");
	rt = get_data();
	rt_init(rt, argv[1]);
	// hello_world(rt);
	// generate_background(rt);
	// generate_sphere_simple(rt);
	
	// test_invsqrt();
	
	t_vec3		sp_center = vec3(0,0,-1);
	generate_sphere_shaded(rt, &sp_center);

	set_hooks(rt);
	mlx_loop(rt->mlx_ptr);

	return (0);
}

#define NB_TESTS 10000000
#include <time.h>
void test_invsqrt() {

	double	start_time = (double)clock();
	double	end_time = (double)clock();
	
	double	time_elapsed = end_time - start_time;
	double tmp;


	for (int i = 0; i < 10; ++i) {

		start_time = (double)clock();

		for (int j = 0 ; j < NB_TESTS; ++j) {
			tmp = 1 / sqrt(rand());
		}
		end_time = (double)clock();
		time_elapsed = end_time - start_time;
		printf("1/sqrt():  %lf ms\n", time_elapsed / 1000);
		
		start_time = (double)clock();

		for (int j = 0 ; j < NB_TESTS; ++j) {
			tmp = invsqrt(rand());
		}
		end_time = (double)clock();
		time_elapsed = end_time - start_time;
		printf("invsqrtf():  %lf ms\n\n", time_elapsed / 1000);
		
	}
	(void)tmp;

}