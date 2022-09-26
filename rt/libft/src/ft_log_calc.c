/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:41:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/11/12 16:41:33 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Fixed to prevent buffer overflow for values close to LONG_MIN/MAX
//by decreasing the value instead of increasing the radix
int	ft_log_calc(int value, int radix)
{
	int		counter;
	long	value_to_long;

	counter = 1;
	value_to_long = value;
	if (value_to_long < 0)
		value_to_long *= -1;
	while (value_to_long >= radix)
	{
		value_to_long /= radix;
		counter++;
	}
	return (counter);
}

int	ft_log_calc_size_t(size_t value, size_t radix)
{
	int		counter;

	counter = 1;
	while (value >= radix)
	{
		value /= radix;
		counter++;
	}
	return (counter);
}
