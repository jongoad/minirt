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

	if (keysym == NUMPAD2 || keysym == KEY_S)
	{
		z_pos	-= 0.05F;
		rt->objs[0]->center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == NUMPAD8 || keysym == KEY_W)
	{
		z_pos	+= 0.05F;
		rt->objs[0]->center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_RIGHT || keysym == KEY_D)
	{
		x_pos	-= 0.1F;
		rt->objs[0]->center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_LEFT || keysym == KEY_A)
	{
		x_pos	+= 0.1F;
		rt->objs[0]->center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_UP)
	{
		y_pos	+= 0.1F;
		rt->objs[0]->center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_DOWN)
	{
		y_pos	-= 0.1F;
		rt->objs[0]->center = vec3(x_pos, y_pos, z_pos);
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	(void) keysym;
	(void) rt;
	return (0);
}
