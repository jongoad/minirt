#include "minirt.h"

/* Check if RGB values are valid */
int check_rgb(char *rgb)
{
	char **split;
	int res;
	t_i i;

	i.x = 0;
	split = ft_split(rgb, ',');
	while (split[i.x])
	{
		res = ft_atoi(split[i.x]);
		if (i.x == 3 || (res < 0 || res > 255))
			return(0);
		i.x++;
	}
	ft_free_split(split);
	if (i.x < 2)
		return (0);
	return (1);
}

/* Check if float is valid, and if applicable if it falls in range*/
int	check_float(char *val, float lim1, float lim2)
{
	float res;

	res = atof(val);  //Need to write atof function

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

/* Check if orientation vector is valid */
int	check_orientation(char *orient)
{
	char **split;
	float res;
	t_i i;

	i.x = 0;
	split = ft_split(orient, ',');
	while (split[i.x])
	{
		res = atof(split[i.x]); //Need to write atof function
		if (i.x == 3 || (res < -1 || res > 1))
			return(0);
		i.x++;
	}
	ft_free_split(split);
	if (i.x < 2)
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
	split = ft_split(coord, ',');
	while (split[i.x])
	{
		res = atof(split[i.x]); //Need to write atof function
		if (i.x == 3) // Need to check not NAN or INF etc.
			return(0);
		i.x++;
	}
	ft_free_split(split);
	if (i.x < 2)
		return (0);
	return (1);
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