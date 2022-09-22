#include "minirt.h"
#include "hooks.h"

void	set_hooks(t_data *rt)
{
	mlx_do_key_autorepeaton(rt->mlx_ptr);
	mlx_key_hook(rt->win_ptr, handle_key_release_hook, rt);
	mlx_mouse_hook(rt->win_ptr, handle_mouse_hook, rt);
	mlx_loop_hook(rt->mlx_ptr, default_hook, rt);
	mlx_hook(rt->win_ptr, DESTROY_NOTIFY, 0, rt_clean_exit, rt);
	mlx_hook(rt->win_ptr, KEYPRESS, KEYPRESS_MASK, handle_key_press_hook, rt);
	mlx_hook(
		rt->win_ptr,
		MOTION_NOTIFY,
		MOUSE_RELEASE_MASK,
		handle_mouse_motion,
		rt);
	mlx_hook(
		rt->win_ptr,
		MOUSE_RELEASE,
		MOUSE_RELEASE_MASK,
		handle_mouse_btn_release,
		rt);
	return ;
}

int	default_hook(t_data *rt)
{
	(void) rt;

	return (0);
}
