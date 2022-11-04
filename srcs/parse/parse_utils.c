#include "minirt.h"

/* Check if RGB values are valid */
int check_rgb(char *rgb)
{
	char **split;
	int res;
	int retval;
	t_i i;

	retval = 1;
	i.x = 0;
	split = ft_split(rgb, ',');
	while (split[i.x])
	{
		res = ft_atoi(split[i.x]);
		if (res < 0 || res > 255)
			retval = 0;
		i.x++;
	}
	ft_free_split(split);
	if (i.x != 3)
		retval = 0;
	return (retval);
}

/* Check if float is valid, and if applicable if it falls in range*/
int	check_float(char *val, float lim1, float lim2)
{
	float res;

	res = atof(val);  //FIXME - Need to write atof function

	//Need to check NAN or inf etc.
	if (lim1 != 0 && lim2 != 0)
		if (res < lim1 || res > lim2)
			return (0);

	return (1);		
}

int check_int(char *val, int lim1, int lim2)
{
	float res;

	res = ft_atoi(val);
	if (lim1 != 0 && lim2 != 0)
		if (res < lim1 || res > lim2)
			return (0); 
	return (1);	
}

/* Check if normal vector is valid */
int	check_orientation(char *orient)
{
	char	**split;
	float	res;
	int		retval;
	t_i		i;

	retval = 1;
	i.x = 0;
	split = ft_split(orient, ',');
	while (split[i.x])
	{
		res = atof(split[i.x]); //Need to write atof function
		if (res < -1 || res > 1)
			retval = 0;
		i.x++;
	}
	ft_free_split(split);
	if (i.x != 3)
		retval = 0;
	return (retval);
}

/* Check if coordinate values are valid */
int	check_coords(char *coord)
{
	char **split;
	t_i i;

	i.x = 0;
	split = ft_split(coord, ',');
	while (split[i.x])
		i.x++;
	ft_free_split(split);
	if (i.x != 3)
		return (0);
	return (1);
}

/* Check if texture/normal path is valid */
int	check_path(char *path, char type)
{
	t_i i;

	i.x = 0;
	while (path[i.x] && path[i.x] != '.')
		i.x++;
	if (type == T_TEXTURE && !ft_strcmp(path, "checkers"))
		return (1);
	else if ((i.x >= 7 && !ft_strncmp(path, "images/", 7)) && (path[i.x] && !ft_strcmp(&path[i.x], ".ppm")))
		return (1);
	return (0);
}

/* Replace all whitespaces with space char */
void	replace_whitespace(t_parse *dat)
{
	t_i i;

	i.y = 0;
	while (dat->split[i.y])
	{
		i.x = 0;
		while (dat->split[i.y][i.x])
		{
			if (is_set(dat->split[i.y][i.x], "\t\v\f\r"))
				dat->split[i.y][i.x] = ' ';
			i.x++;
		}
		i.y++;
	}
}