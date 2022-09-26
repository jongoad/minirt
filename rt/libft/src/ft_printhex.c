/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:50:12 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/10/06 16:25:48 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_writehex(int i, char c)
{
	char	*hex_base;

	if (c == 'x')
		hex_base = "0123456789abcdef";
	else
		hex_base = "0123456789ABCDEF";
	if (i > 15)
		ft_writehex(i / 16, c);
	write(1, &hex_base[i % 16], 1);
}

void	ft_writehex_long(long i)
{
	char	*hex_base;

	hex_base = "0123456789abcdef";
	if (i > 15)
		ft_writehex_long(i / 16);
	write(1, &hex_base[i % 16], 1);
}

static long	power_calc(int base, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (base * power_calc(base, power - 1));
}

static int	get_a_len(unsigned long n)
{
	int	a_len;

	a_len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 16;
		a_len++;
	}
	return (a_len);
}

char	*ft_hextoa(unsigned long n, char c)
{
	int		a_len;
	char	*n_to_a;
	int		i;
	char	*hex_base;

	if (c == 'X')
		hex_base = "0123456789ABCDEF";
	else
		hex_base = "0123456789abcdef";
	i = 0;
	a_len = get_a_len(n);
	n_to_a = malloc(a_len + 1);
	if (!n_to_a)
		return (NULL);
	while (a_len--)
	{
		n_to_a[i++] = hex_base[n / power_calc(16, a_len)];
		n = n % power_calc(16, a_len);
	}
	n_to_a[i] = 0;
	return (n_to_a);
}
