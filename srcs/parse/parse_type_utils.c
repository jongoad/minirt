#include "minirt.h"

/* Check if string represents a valid float */
int validate_float(char *val)
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
			if (!val[i.x + 1] && (val[i.x] == 'f' || val[i.x] == 'F'))	/* If last character if non-numeric and is valid float identifier */
				return(1);
			else if (val[i.x] == '.' && !dot_count && i.x != 0)			/* Check number of period characters */
				dot_count++;
			else
				return (0);
		}
	}
	return (1);
}

/* Check if float is valid, and if applicable if it falls within range */
int	check_float(char *val, float lim1, float lim2)
{
	float res;
	int retval;

	retval = 1;
	if (!validate_float(val))											/* Check if value is valid float */
		retval = 0;
	else if (lim1 != 0.0f || lim2 != 0.0f)								/* If limits provided, check if value falls within range */
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
int check_int(char *val, int lim1, int lim2)
{
	float	res;
	int		retval;
	t_i 	i;

	retval = 1;
	i.x = -1;
	while (val[++i.x])
		if (!ft_isdigit(val[i.x]))										/* Check if valid integer value */
			retval = 0;
	res = ft_atoi(val);
	if (lim1 != 0 && lim2 != 0)											/* If limits provided, check if value falls within range */	
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
