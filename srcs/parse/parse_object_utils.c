#include "minirt.h"

/* Check if RGB values are valid */
int check_rgb(char *rgb)
{
	char	**split;
	int		res;
	int		retval;
	t_i		i;

	retval = 1;
	i.x = 0;
	split = ft_split(rgb, ',');											/* Split into component RGB strings */
	while (split[i.x])
	{
		res = ft_atoi(split[i.x]);										/* Convert to integer and check if value is within range */
		if (res < 0 || res > 255)
			retval = 0;
		i.x++;
	}
	ft_free_split(split);
	if (i.x != 3)
		retval = 0;
	if (retval == 0)													/* Return error if value invalid or not correct number of values */
	{
		ft_putstr_fd("Error: invalid RGB data\n", 2);
		fprintf(stderr, "\t%s\n", rgb);
	}
	return (retval);
}

/* Check if normal vector is valid */
int	check_orientation(char *orient)
{
	char	**split;
	int		retval;
	t_i		i;

	retval = 1;
	i.x = 0;
	split = ft_split(orient, ',');										/* Split into vector components */
	while (split[i.x])
	{
		if (!check_float(split[i.x], -1.0f, 1.0f))						/* Check if float is valid and falls within range */
		{
			retval = 0;
			break ;
		}
		i.x++;
	}
	if (i.x != 3 || !check_orient_zero(split))
		retval = 0;
	ft_free_split(split);
	if (retval == 0)
		ft_putstr_fd(PARSE_ERR_ORIENT, 2);
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
	split = ft_split(coord, ',');										/* Split into vector components */
	while (split[i.x])
	{
		if (!check_float(split[i.x], 0.0f, 0.0f))						/* Check if float is valid */
		{
			retval = 0;
			break ;
		}
		i.x++;
	}
	ft_free_split(split);
	if (i.x != 3)
		retval = 0;
	if (retval == 0)
		ft_putstr_fd(PARSE_ERR_POS, 2);
	return (retval);
}

/* Check if texture/normal path is valid */
int	check_path(char *path, char type)
{
	t_i i;

	i.x = 0;
	while (path[i.x] && path[i.x] != '.')								/* Increment until file suffix */
		i.x++;
	if (type == T_TEXTURE && !ft_strcmp(path, "checkers"))				/* Check if checkers keyword is provided instead of filepath */
		return (1);
	else if ((i.x >= 7 && !ft_strncmp(path, "images/", 7))				/* Check if filepath follows valid syntax and has proper filetype */
		&& (path[i.x] && !ft_strcmp(&path[i.x], ".ppm")))
		return (1);
	ft_putstr_fd("Error: invalid filepath or texture descriptor\n", 2);
	fprintf(stderr, "\t%s\n", path);
	return (0);
}
