#include "minirt.h"
#include "hooks.h"

int	handle_mouse_hook(int button, int x, int y, t_data *rt)
{
	if (button == 1)
	{

		(void)rt;
		(void)x;
		(void)y;
		printf("mouse btn1 clicked at [%d, %d]\n", x, y);
		// rt->toggle_mouse_rot = !rt->toggle_mouse_rot;
		// if (rt->toggle_mouse_rot)
		// {
		// 	rt->toggle_rot_x = false;
		// 	rt->toggle_rot_y = false;
		// 	rt->toggle_rot_z = false;
		// 	rt->mouse_initial_xy = (x << 16) | y;
		// }
	}
	return (0);
}

int	handle_mouse_motion(int x, int y, t_data *rt)
{
	double	x_percent;
	double	y_percent;

	x_percent = (double)x / (double)rt->win_w;
	(void)x_percent;
	y_percent = (double)y / (double)rt->win_h;
	(void)y_percent;
	// printf("x_percent = %f\ny_percent = %f]\n", x_percent, y_percent);
	(void) rt;
	return (0);
}