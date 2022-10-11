#include "minirt.h"
#include "hooks.h"

static int	handle_key_press_hook_rt_one_weekend(int keysym, t_data *rt);

int	handle_key_release_hook(int keysym, t_data *rt)
{
	if (keysym == KEY_ESC)
		rt_clean_exit(rt);
	if (keysym == KEY_L)
		rt->apply_light_halos = !(rt->apply_light_halos);
	// render_scene(rt, rt->objs[0]);
	return (0);
}

// int	handle_key_press_hook(int keysym, t_data *rt)
// {
// 	if (rt->cam.is_move)
// 	{
// 		if (keysym == KEY_W)			/* Move camera forwards */
// 			rt->cam.translate.z -= 0.1f;
// 		if (keysym == KEY_S)			/* Move camera backwards */
// 			rt->cam.translate.z += 0.1f;
// 		if (keysym == KEY_A)			/* Move camera left */
// 			rt->cam.translate.x -= 0.1f;
// 		if (keysym == KEY_D)			/* Move camera right */
// 			rt->cam.translate.x += 0.1f;
// 		if (keysym == KEY_Q)			/* Move camera down */
// 			rt->cam.translate.y -= 0.1f;
// 		if (keysym == KEY_E)			/* Move camera up */
// 			rt->cam.translate.y += 0.1f;

// 		cam_recalc(rt);
// 		render_scene(rt, rt->objs[0]);
// 	}
// 	return (0);
// }

int	handle_key_press_hook(int keysym, t_data *rt)
{
	return (handle_key_press_hook_rt_one_weekend(keysym, rt));
}



static int	handle_key_press_hook_rt_one_weekend(int keysym, t_data *rt)
{
	printf("key = %d\n", keysym);
	if (keysym == NUMPAD2 || keysym == KEY_S)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->center.z -= 0.05F;
			printf("center.z = %f\n", rt->objs[rt->selected_obj_id]->center.z);
		}
		else
		{
			rt->cam.pos.z -= 0.05F;
		}
	}
	else if (keysym == NUMPAD8 || keysym == KEY_W)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->center.z += 0.05F;
			printf("center.z = %f\n", rt->objs[rt->selected_obj_id]->center.z);
		}
		else
		{
			rt->cam.pos.z += 0.05F;
		}
	}
	else if (keysym == KEY_RIGHT || keysym == KEY_D)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->center.x -= 0.1F;
			printf("center.x = %f\n", rt->objs[rt->selected_obj_id]->center.x);
		}
		else
		{
			rt->cam.pos.x -= 0.1F;
		}
	}
	else if (keysym == KEY_LEFT || keysym == KEY_A)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->center.x += 0.1F;
			printf("center.x = %f\n", rt->objs[rt->selected_obj_id]->center.x);
		}
		else
		{
			rt->cam.pos.x += 0.1F;
		}
	}
	else if (keysym == KEY_UP || keysym == KEY_X)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->center.y += 0.1F;
			rt->objs[rt->selected_obj_id]->cyl_offset += 0.1F;
			printf("center.y = %f\n", rt->objs[rt->selected_obj_id]->center.y);
		}
		else
		{
			rt->cam.pos.y += 0.1F;
		}
	}
	else if (keysym == KEY_DOWN || keysym == KEY_Z)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->center.y -= 0.1F;
			rt->objs[rt->selected_obj_id]->cyl_offset -= 0.1F;
			printf("center.y = %f\n", rt->objs[rt->selected_obj_id]->center.y);
		}
		else
		{
			rt->cam.pos.y -= 0.1F;
		}
	}
	else if (keysym == KEY_PLUS || keysym == NUMPAD_PLUS)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			rt->objs[rt->selected_obj_id]->radius += 0.01;
		}
	}
	else if (keysym == KEY_MINUS || keysym == NUMPAD_MINUS)
	{
		if (rt->selected_obj_id != NO_HIT)
		{
			if (rt->objs[rt->selected_obj_id]->radius > 0.05F)
				rt->objs[rt->selected_obj_id]->radius -= 0.01;
		}
	}
	else
		return (0);

	cam_recalc(rt);
	render_scene(rt, rt->objs[0]);
	return (0);
}
