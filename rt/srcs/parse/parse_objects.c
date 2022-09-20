#include "../../includes/minirt.h"

/* Parse ambient light (A) */
int	parse_ambient(char **obj)
{
	t_i i;

	i.x = 0;
	if (ft_strcmp(obj[0], "A"))
		return (0);
	while (obj[i.x])
		i.x++;
	if (i.x != 2)
		return (0);
	else if (!check_float(obj[1], 0, 1)) //Check lighting ratio
		return (0);
	else if (!check_rgb(obj[2])) // Check RGB
		return (0);
	return (1);

}

/* Parse camera (C) */
int	parse_camera(char **obj)
{
	t_i i;

	i.x = 0;
	if (ft_strcmp(obj[0], "C"))
		return (0);
	while (obj[i.x])
		i.x++;
	if (i.x != 2)
		return (0);
	if (!check_coords(obj[1])) //Check xyz coords
		return (0);
	else if (!check_orientation(obj[2])) //Check orientation vector
		return (0);
	else if (!check_int(obj[2], 0, 180))  //Check FOV range
		return (0);
	return (1);
}

/* Parse point light (L) */
int	parse_light(char **obj)
{
	t_i i;

	i.x = 0;
	if (ft_strcmp(obj[0], "L"))
		return (0);
	while (obj[i.x])
		i.x++;
	if (BONUS == 1 && i.x != 3)
		return (0);
	else if (BONUS == 0 && i.x != 2)
	if (!check_coords(obj[1])) // Check coords
		return (0);
	else if (!check_float(obj[3], 0, 1)) //Check lighting ratio
		return (0);
	if (BONUS == 1)
		if (!check_rgb(obj[5])) // Check RGB
		return (0);
	return (1);
}

/* Parse plane (pl) */
int parse_plane(char **obj)
{
	t_i i;

	i.x = 0;
	if (ft_strcmp(obj[0], "pl"))
		return (0);
	while (obj[i.x])
		i.x++;
	if (i.x != 3)
		return (0);
	if (!check_coords(obj[1])) //Check xyz coords
		return (0);
	else if (!check_orientation(obj[2])) //Check orientation vector
		return (0);
	else if (!check_rgb(obj[3])) //Check RBG colours
		return (0);
	return (1);
}

/* Parse sphere (sp) */
int	parse_sphere(char **obj)
{
	t_i i;

	i.x = 0;
	if (ft_strcmp(obj[0], "sp"))
		return (0);
	while (obj[i.x])
		i.x++;
	if (i.x != 3)
		return (0);
	if (!check_coords(obj[1])) //Check xyz coords
		return (0);
	else if (!check_float(obj[2], 0, 0)) //Check diameter
		return (0);
	else if (!check_rgb(obj[3])) //Check RBG colours
		return (0);
	return (1);
}

/* Parse cylinder (cy) */
int	parse_cylinder(char **obj)
{
	t_i i;

	i.x = 0;
	if (ft_strcmp(obj[0], "cy"))
		return (0);
	while (obj[i.x])
		i.x++;
	if (i.x != 5)
		return (0);
	if (!check_coords(obj[2]))
		return (0);
	else if (!check_orientation(obj[3])) //Check orientation vector
		return (0);
	else if (!check_float(obj[3], 0, 0)) //Check diameter
		return (0);
	else if (!check_float(obj[3], 0, 0)) //Check height
		return (0);
	else if (!check_rgb(obj[5]))
		return (0);
	return (1);
}

/* Check if coordinate values are valid */
int	check_coords(char *coord)
{
	char **split;
	float res;
	t_i i;

	i.x = 0;
	split = ft_split(coord, ",");
	while (split[i.x])
	{
		res = ft_atof(split[i.x]); //Need to write atof function
		if (i.x == 3) // Need to check not NAN or INF etc.
		{
			ft_free_split(split);
			return(0);
		}
		ft_free_split(split);
		i.x++;
	}
	if (i.x < 2)
		return (0);
	return (1);
}

/* Check if orientation vector is valid */
int	check_orientation(char *orient)
{
	char **split;
	float res;
	t_i i;

	i.x = 0;
	split = ft_split(orient, ",");
	while (split[i.x])
	{
		res = ft_atof(split[i.x]); //Need to write atof function
		if (i.x == 3 || (res < -1 || res > 1))
		{
			ft_free_split(split);
			return(0);
		}
		ft_free_split(split);
		i.x++;
	}
	if (i.x < 2)
		return (0);
	return (1);
}

/* Check if RGB values are valid */
int check_rgb(char *rgb)
{
	char **split;
	int res;
	t_i i;

	i.x = 0;
	split = ft_split(rgb, ",");
	while (split[i.x])
	{
		res = ft_atoi(split[i.x]);
		if (i.x == 3 || (res < 0 || res > 255))
		{
			ft_free_split(split);
			return(0);
		}
		ft_free_split(split);
		i.x++;
	}
	if (i.x < 2)
		return (0);
	return (1);
}

/* Check if float is valid, and if applicable if it falls in range*/
int	check_float(char *val, float lim1, float lim2)
{
	float res;

	res = ft_atof(val);  //Need to write atof function

	//Need to check NAN or inf etc.
	if (lim1 != 0 && lim2 != 0)
		if (res < lim1 || res > lim2)
			return (0);

	return (1);		
}

int check_int(char *val, int lim1, int lim2)
{
	char **split;
	float res;
	t_i i;

	i.x = 0;
	split = ft_split(val, ",");
	while (split[i.x])
		i.x++;
	if (i.x != 1)
		return (0);
	res = ft_atoi(split[0]);
	if (lim1 != 0 && lim2 != 0)
		if (res < lim1 || res > lim2)
			return (0);
	res = ft_atoi(split[1]);
	if (lim1 != 0 && lim2 != 0)
		if (res < lim1 || res > lim2)
			return (0);
	
	return (1);	
}
