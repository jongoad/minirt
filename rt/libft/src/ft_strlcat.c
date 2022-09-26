/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:53:35 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/27 15:45:56 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	total_length;

	i = 0;
	total_length = ft_strlen(src) + ft_strlen(dst);
	while (*dst && i < dstsize)
	{
		dst++;
		i++;
	}
	if (i == dstsize)
		return (dstsize + ft_strlen(src));
	while (++i < dstsize && *src)
		*dst++ = *src++;
	*dst = 0;
	return (total_length);
}
