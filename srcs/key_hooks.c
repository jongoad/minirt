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
	if (keysym == NUMPAD2 || keysym == KEY_S)
	{
		if (rt->selected_obj_id == NO_HIT)
			rt->cam.pos.z -= 0.05F;
		else
		{
			rt->objs[rt->selected_obj_id]->center.z -= 0.05F;
			printf("center.z = %f\n", rt->objs[rt->selected_obj_id]->center.z);
		}
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == NUMPAD8 || keysym == KEY_W)
	{
		if (rt->selected_obj_id == NO_HIT)
			rt->cam.pos.z += 0.05F;
		else
		{
			rt->objs[rt->selected_obj_id]->center.z += 0.05F;
			printf("center.z = %f\n", rt->objs[rt->selected_obj_id]->center.z);
		}
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_RIGHT || keysym == KEY_D)
	{
		if (rt->selected_obj_id == NO_HIT)
			rt->cam.pos.x -= 0.1F;
		else
		{
			rt->objs[rt->selected_obj_id]->center.x -= 0.1F;
			printf("center.x = %f\n", rt->objs[rt->selected_obj_id]->center.x);
		}
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_LEFT || keysym == KEY_A)
	{
		if (rt->selected_obj_id == NO_HIT)
			rt->cam.pos.x += 0.1F;
		else
		{
			rt->objs[rt->selected_obj_id]->center.x += 0.1F;
			printf("center.x = %f\n", rt->objs[rt->selected_obj_id]->center.x);
		}
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_UP || keysym == KEY_X)
	{
		if (rt->selected_obj_id == NO_HIT)
			rt->cam.pos.y += 0.1F;
		else
		{
			rt->objs[rt->selected_obj_id]->center.y += 0.1F;
			printf("center.y = %f\n", rt->objs[rt->selected_obj_id]->center.y);
		}
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_DOWN || keysym == KEY_Z)
	{
		if (rt->selected_obj_id == NO_HIT)
			rt->cam.pos.y -= 0.1F;
		else
		{
			rt->objs[rt->selected_obj_id]->center.y -= 0.1F;
			printf("center.y = %f\n", rt->objs[rt->selected_obj_id]->center.y);
		}
		generate_sphere_shaded(rt, rt->objs[0]);
	}
	else if (keysym == KEY_PLUS || keysym == NUMPAD_PLUS)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->radius += 0.01;
			generate_sphere_shaded(rt, rt->objs[0]);
		}
	}
	else if (keysym == KEY_MINUS || keysym == NUMPAD_MINUS)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			if (rt->objs[0]->radius > 0.05F)
				rt->objs[rt->selected_obj_id]->radius -= 0.01;
			generate_sphere_shaded(rt, rt->objs[0]);
		}
	}

	(void) keysym;
	(void) rt;
	return (0);
}
