/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:37:00 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/03/25 18:41:42 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int a, int b)
{
	return ((a >= b) * a + (b > a) * b);
}

int	ft_min(int a, int b)
{
	return ((a <= b) * a + (b < a) * b);
}

int	ft_abs(int a)
{
	return ((a >= 0) * a + (a < 0) * (-a));
}

bool	ft_same_sign(int a, int b)
{
	return ((a >= 0 && b >= 0) || ((a < 0) && (b < 0)));
}
