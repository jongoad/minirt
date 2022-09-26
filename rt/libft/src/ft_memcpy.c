/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:53:40 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/22 19:44:20 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;

	if (!dest && !src)
		return (NULL);
	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	while (n--)
	{
		*dest_ptr++ = *src_ptr++;
	}
	return (dest);
}
