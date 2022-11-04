#include "minirt.h"

/* Parse ambient light (A) */
int	parse_ambient(char **obj)
{
	t_i i;

	i.x = 0;
	if (ft_strcmp(obj[0], "A"))
		return (0);
	while (obj[i.x])
		i.x++;
	if (i.x != 3)
		return (0);
	if (!check_float(obj[1], 0, 1)) //Check lighting ratio
		return (0);
	if (!check_rgb(obj[2])) // Check RGB
		return (0);
	return (1);
}

/* Parse camera (C) */
int	parse_camera(char **obj)
{
	t_i i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x != 4)
		return (0);
	if (!check_coords(obj[1])) //Check xyz coords
		return (0);
	if (!check_orientation(obj[2])) //Check orientation vector
		return (0);
	if (!check_int(obj[3], 0, 180))  //Check FOV range
		return (0);
	return (1);
}

/* Parse point light (L) */
int	parse_light(char **obj)
{
	t_i i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (BONUS == 1 && i.x != 4)
		return (0);
	if (BONUS == 0 && i.x != 3)
		return (0);
	if (!check_coords(obj[1])) // Check coords
		return (0);
	if (!check_float(obj[2], 0, 1)) //Check lighting ratio
		return (0);
	
	if (BONUS == 1)
	{
		if (!check_rgb(obj[3])) // Check RGB
		return (0);
	}
	return (1);
}

/* Parse plane (pl) */
int parse_plane(char **obj)
{
	t_i i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x != 4 && !BONUS)
		return (0);
	else if (i.x != 7 && BONUS)
		return (0);
	if (!check_coords(obj[1])) //Check xyz coords
		return (0);
	if (!check_orientation(obj[2])) //Check orientation vector
		return (0);
	if (!check_rgb(obj[3])) //Check RBG colours
		return (0);
	if (BONUS)
	{
		if (!check_float(obj[4], 0, 0))							/* Check shininess */
			return (0);
		else if (!check_path(obj[5], T_TEXTURE) || !check_path(obj[6], T_NORMAL))	/* Check texture and normal */
			return (0);
	}
	return (1);
}

/* Parse sphere (sp) */
int	parse_sphere(char **obj)
{
	t_i i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x != 4 && !BONUS)
		return (0);
	else if (i.x != 7 && BONUS)
		return (0);
	if (!check_coords(obj[1])) //Check xyz coords
		return (0);
	else if (!check_float(obj[2], 0, 0)) //Check diameter
		return (0);
	else if (!check_rgb(obj[3])) //Check RBG colours
		return (0);
	if (BONUS)
	{
		if (!check_float(obj[4], 0, 0))
			return (0);
		else if (!check_path(obj[5], T_TEXTURE) || !check_path(obj[6], T_NORMAL))
			return (0);
	}
	return (1);
}

/* Parse cylinder (cy) */
int	parse_cylinder(char **obj)
{
	t_i i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x != 6 && !BONUS)
		return (0);
	else if (i.x != 9 && BONUS)
		return (0);
	if (!check_coords(obj[1]))
		return (0);
	if (!check_orientation(obj[2])) //Check orientation vector
		return (0);
	if (!check_float(obj[3], 0, 0)) //Check diameter
		return (0);
	if (!check_float(obj[4], 0, 0)) //Check height
		return (0);
	if (!check_rgb(obj[5]))
		return (0);
	if (BONUS)
	{
		if (!check_float(obj[6], 0, 0))
			return (0);
		else if (!check_path(obj[7], T_TEXTURE) || !check_path(obj[8], T_NORMAL))
			return (0);
	}
	return (1);
}

/* Parse cone (co) */
int	parse_cone(char **obj)
{
	t_i i;

	i.x = 0;
	while (obj[i.x])
		i.x++;
	if (i.x != 9)
		return (0);
	else if (!check_coords(obj[1]))
		return (0);
	else if (!check_orientation(obj[2])) //Check orientation vector
		return (0);
	else if (!check_float(obj[3], 0, 0)) //Check diameter
		return (0);
	else if (!check_float(obj[4], 0, 0)) //Check height
		return (0);
	else if (!check_rgb(obj[5]))
		return (0);
	else if (!check_float(obj[6], 0, 0))
		return (0);
	else if (!check_path(obj[7], T_TEXTURE) || !check_path(obj[8], T_NORMAL))
		return (0);
	return (1);
}