#include "minirt.h"
#include "hooks.h"

static int	handle_key_press_hook_rt_one_weekend(int keysym, t_data *rt);

int	handle_key_release_hook(int keysym, t_data *rt)
{
	if (keysym == KEY_ESC)
		rt_clean_exit(rt);
	return (0);
}

int	handle_key_press_hook(int keysym, t_data *rt)
{
	return (handle_key_press_hook_rt_one_weekend(keysym, rt));
}

static int	handle_key_press_hook_rt_one_weekend(int keysym, t_data *rt)
{
	static double	y_pos;
	static double	x_pos;
	static double	z_pos = -1.0F;
	t_vec3			sp_center;
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
	if (keysym == NUMPAD2 || keysym == KEY_S)
	{
		z_pos	-= 0.1F;
		sp_center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, &sp_center);
	}
	else if (keysym == NUMPAD8 || keysym == KEY_W)
	{
		z_pos	+= 0.1F;
		sp_center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, &sp_center);
	}
	else if (keysym == KEY_RIGHT || keysym == KEY_D)
	{
		x_pos	-= 0.1F;
		sp_center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, &sp_center);
	}
	else if (keysym == KEY_LEFT || keysym == KEY_A)
	{
		x_pos	+= 0.1F;
		sp_center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, &sp_center);
	}
	else if (keysym == KEY_UP)
	{
		y_pos	+= 0.1F;
		sp_center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, &sp_center);
	}
	else if (keysym == KEY_DOWN)
	{
		y_pos	-= 0.1F;
		sp_center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, &sp_center);
	}
	(void) keysym;
	(void) rt;
	return (0);
}
