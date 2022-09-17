/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:15:43 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/16 15:58:57 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
