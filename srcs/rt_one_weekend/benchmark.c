#include "minirt.h"
#include <time.h>

void	display_fps(t_data *rt, double start_time)
{
	// Benchmarking
	float	end_time = (float)clock();
	float	time_elapsed;
	char 	buff[10];
	char	*fps;

	time_elapsed = end_time - start_time;
	g_fps = 1000000 / time_elapsed;
	
	snprintf(buff, 10, "%.2lf", g_fps);
	fps = ft_strjoin(buff, " fps");
	
	// Causes leaks...
	mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 10, RED, fps);

	free(fps);
	
	printf("Render time: %.2lf ms\n", time_elapsed / 1000);
	printf("FPS: %.2lf\n", g_fps);
}
