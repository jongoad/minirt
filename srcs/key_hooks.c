#include "minirt.h"
#include "hooks.h"

int	handle_key_release_hook(int keysym, t_data *rt)
{
	if (keysym == KEY_ESC)
		rt_clean_exit(rt);
	// if (keysym == KEY_F1)
	// {
	// 	rt->toggle_menu = !rt->toggle_menu;
	// 	display_menu(rt);
	// 	return (0);
	// }
	// if (rt->toggle_menu)
	// 	return (1);
	// else if (keysym == KEY_C)
	// 	rt->map_is_colored = !rt->map_is_colored;
	// else if (keysym == KEY_P)
	// 	rt->toggle_proj = !rt->toggle_proj;
	// else if (keysym == KEY_R)
	// 	toggle_all_rotations(rt);
	// else if (keysym == NUMPAD9)
	// 	rt->toggle_rot_z = !rt->toggle_rot_z;
	// else if (keysym == NUMPAD6)
	// 	rt->toggle_rot_y = !rt->toggle_rot_y;
	// else if (keysym == NUMPAD3)
	// 	rt->toggle_rot_x = !rt->toggle_rot_x;
	// else if (keysym == NUMPAD0 || keysym == KEY_0)
	// 	reset_proportions(rt);
	return (0);
}

int	handle_key_press_hook(int keysym, t_data *rt)
{
	// if (rt->toggle_menu)
	// 	return (1);
	// if (keysym == NUMPAD_PLUS || keysym == KEY_PLUS)
	// 	if (rt->square_width < 150)
	// 		rt->square_width += 1;
	// if (keysym == NUMPAD_MINUS || keysym == KEY_MINUS)
	// 	if (rt->square_width > 2)
	// 		rt->square_width -= 1;
	// if (keysym == NUMPAD7)
	// 	rt->theta_z -= 0.1;
	// if (keysym == NUMPAD8)
	// 	rt->theta_z += 0.1;
	// if (keysym == NUMPAD4)
	// 	rt->theta_y -= 0.1;
	// if (keysym == NUMPAD5)
	// 	rt->theta_y += 0.1;
	// if (keysym == NUMPAD1)
	// 	rt->theta_x -= 0.1;
	// if (keysym == NUMPAD2)
	// 	rt->theta_x += 0.1;
	// if (rt->toggle_proj && keysym == KEY_O)
	// 	cycle_orthographic_perspectives(rt);
	return (handle_key_press_hook_2(keysym, rt));
}

int	handle_key_press_hook_2(int keysym, t_data *rt)
{
	// if (keysym == KEY_W)
	// 	if (rt->z_offset > -1000)
	// 		rt->z_offset -= 8;
	// if (keysym == KEY_S)
	// 	if (rt->z_offset < 2000)
	// 		rt->z_offset += 8;
	// if (keysym == KEY_Q)
	// 	if (rt->z_divisor > -5)
	// 		rt->z_divisor -= 0.12;
	// if (keysym == KEY_E)
	// 	if (rt->z_divisor < 5)
	// 		rt->z_divisor += 0.12;
	// if (keysym == KEY_LEFT || keysym == KEY_A)
	// 	if (rt->x_offset < rt->win_w * 0.1F * rt->square_width)
	// 		rt->x_offset += 10;
	// if (keysym == KEY_RIGHT || keysym == KEY_D)
	// 	if (rt->x_offset > rt->win_w * -0.1F * rt->square_width)
	// 		rt->x_offset -= 10;
	// if (keysym == KEY_UP || keysym == KEY_Z)
	// 	if (rt->y_offset < rt->win_h * 0.1F * rt->square_width)
	// 		rt->y_offset += 10;
	// if (keysym == KEY_DOWN || keysym == KEY_X)
	// 	if (rt->y_offset > rt->win_h * -0.1F * rt->square_width)
	// 		rt->y_offset -= 10;
	(void) keysym;
	(void) rt;
	return (0);
}
