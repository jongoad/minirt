#include "minirt.h"
#include "hooks.h"

int	handle_mouse_hook(int button, int x, int y, t_data *cont)
{
	if (button == 1)
	{

		x = y + cont->win_w;
		printf("mouse btn1 clicked at [%d, %d]\n", x, y);
		// cont->toggle_mouse_rot = !cont->toggle_mouse_rot;
		// if (cont->toggle_mouse_rot)
		// {
		// 	cont->toggle_rot_x = false;
		// 	cont->toggle_rot_y = false;
		// 	cont->toggle_rot_z = false;
		// 	cont->mouse_initial_xy = (x << 16) | y;
		// }
	}
	return (0);
}

int	handle_mouse_motion(int x, int y, t_data *cont)
{
	double	x_percent;
	double	y_percent;

	x_percent = (double)x / (double)cont->win_w;
	y_percent = (double)y / (double)cont->win_h;
	printf("x_percent = %f\ny_percent = %f]\n", x_percent, y_percent);
	(void) cont;
	return (0);
}
