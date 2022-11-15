#include "minirt.h"
#include "hooks.h"

/* Main data structure singleton fetch function */
t_data	*get_data(void)
{
	static t_data	*data;

	if (!data)
		data = ft_xalloc(sizeof(t_data));
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*rt;

	if (argc != 2)
		exit_on_err(BAD_ARG_ERR);
	rt = get_data();
	if (!parse(rt, argv[1]))
		return (0);
	rt_init(rt, argv[1]);
	set_hooks(rt);
	cam_init(rt);
	render_scene(rt);
	display_default(rt);
	mlx_loop(rt->mlx_ptr);
	return (0);
}
