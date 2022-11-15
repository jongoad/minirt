#include "minirt.h"

/* Check if string represents a valid float */
int	validate_float(char *val)
{
	t_i	i;
	int	dot_count;

	i.x = -1;
	dot_count = 0;
	while (val[++i.x])
	{
		if (!ft_isdigit(val[i.x]))
		{
			if (i.x == 0 && (val[i.x] == '-' || val[i.x] == '+'))
				continue ;
			if (!val[i.x + 1] && (val[i.x] == 'f' || val[i.x] == 'F'))
				return (1);
			else if (val[i.x] == '.' && !dot_count && i.x != 0)
				dot_count++;
			else
				return (0);
		}
	}
	return (1);
}

/* Check if orientation contains a single non-zero value */
bool	check_orient_zero(char **split)
{
	int		i;
	bool	is_val;
	float	res;

	i = 0;
	is_val = false;
	while (split[i])
	{
		res = ft_atof(split[i]);
		if (res != 0.0f)
		{
			is_val = true;
			break ;
		}
		i++;
	}
	return (is_val);
}

/* Check if float is valid, and if applicable if it falls within range */
int	check_float(char *val, float lim1, float lim2)
{
	float	res;
	int		retval;

	retval = 1;
	if (!validate_float(val))
		retval = 0;
	else if (lim1 != 0.0f || lim2 != 0.0f)
	{
		res = ft_atof(val);
		if (res < lim1 || res > lim2)
			retval = 0;
	}
	if (retval == 0)
	{
		ft_putstr_fd(PARSE_ERR_FLOAT, 2);
		fprintf(stderr,
			"\tfloat value: %s\n\trange min: %f\n\trange max: %f\n",
			val, lim1, lim2);
	}
	return (retval);
}

/* Check if integer is valid, and if applicable if it falls within range */
int	check_int(char *val, int lim1, int lim2)
{
	float	res;
	int		retval;
	t_i		i;

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
		ft_putstr_fd(PARSE_ERR_INT, 2);
		fprintf(stderr,
			"\tint value: %s\n\trange min: %i\n\trange max: %i\n",
			val, lim1, lim2);
	}
	return (retval);
}
