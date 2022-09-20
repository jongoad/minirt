#include <stdio.h>
#include <math.h>
#include "../libft/libft.h"

unsigned int	ft_atox(char *str)
{
	char			*hex_base_lower;
	char			*hex_base_upper;
	unsigned int	atox;
	int				i;

	hex_base_lower = "0123456789abcdef";
	hex_base_upper = "0123456789ABCDEF";
	atox = 0; 
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	i += 2;
	while (is_set(str[i], hex_base_lower) || is_set(str[i], hex_base_upper))
	{
		if (ft_isdigit(str[i]))
			atox = (str[i] - '0') + atox * 16;
		else if (is_set(str[i], hex_base_lower))
			atox = (str[i] - 'a' + 10) + atox * 16;
		else
			atox = (str[i] - 'A' + 10) + atox * 16;
		i++;
	}
	return (atox);
}

double	fdf_strtodbl(char *str, char **endptr)
{
	int				integer;
	unsigned int	decimal;
	int				index;

	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || ft_isdigit(str[index]))
	{
		integer = ft_atoi(&str[index]);
		index += log10(integer);
		printf("integer = %d \n", integer);
		if (integer < 0)
			index++;
	}
	if (str[index] == ',')
	{
		index++;
		decimal = ft_atox(&str[index]);
	}
	while (is_set(str[index], "0123456789ABCDEFabcdefx"))
		index++;
	*endptr = &str[index];
	return (integer + (decimal / __exp10(log10(decimal))));
}


int	main(void)
{
	double	dbl;
	char	*endptr;

	endptr = NULL;
	dbl = fdf_strtodbl("200,0xFF0000", &endptr);
	printf("dbl = %f \n", dbl);
	printf("endptr = %p \n", endptr);
	return (0);
}
