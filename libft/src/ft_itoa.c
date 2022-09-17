/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:34:58 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/23 11:16:24 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	power_calc(int base, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (base * power_calc(base, power - 1));
}

static int	get_a_len(int n)
{
	int	a_len;

	a_len = 0;
	if (!n)
		return (1);
	if (n < 0)
		a_len++;
	while (n)
	{
		n /= 10;
		a_len++;
	}
	return (a_len);
}

char	*ft_itoa(int n)
{
	int		a_len;
	char	*n_to_a;
	long	i;
	long	n_to_long;

	n_to_long = (long)n;
	i = 0;
	a_len = get_a_len(n_to_long);
	n_to_a = malloc(a_len + 1);
	if (!n_to_a)
		return (NULL);
	if (n_to_long < 0)
	{
		n_to_a[i++] = '-';
		n_to_long *= -1;
		a_len--;
	}
	while (a_len--)
	{
		n_to_a[i++] = (n_to_long / power_calc(10, a_len)) + '0';
		n_to_long = n_to_long % power_calc(10, a_len);
	}
	n_to_a[i] = 0;
	return (n_to_a);
}
