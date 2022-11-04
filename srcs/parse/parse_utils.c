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
	if (retval == 0)
	{
		ft_putstr_fd("Error: invalid RGB data\n", 2);
		fprintf(stderr, "\t%s\n", rgb);
	}
	return (retval);
}


int parse_float(char *val)
{
	t_i	i;
	int	dot_count;

	i.x = 0;
	dot_count = 0;
	while (val[i.x])
	{
		if (!ft_isdigit(val[i.x]))
		{
			if (!val[i.x + 1] && (val[i.x] != 'f' || val[i.x] != 'F'))
				return(0);
			if (val[i.x] == '.' && !dot_count && i.x != 0)
				dot_count++;
			else
				return (0);
		}
		i.x++;
	}
	return (1);
}

/* Check if float is valid, and if applicable if it falls in range*/
int	check_float(char *val, float lim1, float lim2)
{
	float res;
	int retval;

	res = atof(val);  //FIXME - Need to write atof function
	retval = 1;
	if (!parse_float(val))
		retval = 0;
	else if (lim1 != 0.0f || lim2 != 0.0f)
		if (res < lim1 || res > lim2)
			retval = 0;
	if (retval == 0)
	{
		ft_putstr_fd("Error: float value is out of defined range or invalid\n", 2);
		fprintf(stderr, "\tfloat value: %s\n\trange min: %f\n\trange max: %f\n", val, lim1, lim2);
	}
	return (retval);		
}

int check_int(char *val, int lim1, int lim2)
{
	float	res;
	int		retval;
	t_i 	i;

	retval = 1;
	i.x = -1;
	while (val[++i.x])
		if (!ft_isdigit(val[i.x]))
			retval = 0;
	res = ft_atoi(val);
	if (lim1 != 0 && lim2 != 0)
		if (res < lim1 || res > lim2)
			retval = 0; 
	if (retval == 0)
	{
		ft_putstr_fd("Error: int value is out of defined range\n", 2);
		fprintf(stderr, "\tint value: %s\n\trange min: %i\n\trange max: %i\n", val, lim1, lim2);
	}
	return (retval);	
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
	if (retval == 0)
	{
		ft_putstr_fd("Error: orientation values are out of defined range or invalid\n", 2);
		fprintf(stderr, "\torientation: %s\n\trange min: -1.0\n\trange max: 1.0\n", orient);
	}
	return (retval);
}

/* Check if coordinate values are valid */
int	check_coords(char *coord)
{
	char	**split;
	int		retval;
	t_i i;

	retval = 1;
	i.x = 0;
	split = ft_split(coord, ',');
	while (split[i.x])
		i.x++;
	ft_free_split(split);
	if (i.x != 3)
		retval = 0;
	if (retval == 0)
	{
		ft_putstr_fd("Error: invalid coordinate data for object\n", 2);
		fprintf(stderr, "\t%s\n", coord);
	}
	return (retval);
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
	ft_putstr_fd("Error: invalid filepath or texture descriptor\n", 2);
	fprintf(stderr, "\t%s\n", path);
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