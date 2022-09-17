/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:39:37 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/23 10:13:59 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*(src + i) != '\0' && i < dstsize)
	{
		*dst++ = *(src + i);
		i++;
	}
	if (i < dstsize)
		*dst = 0;
	else if (dstsize)
		*(dst - 1) = 0;
	return (ft_strlen(src));
}
