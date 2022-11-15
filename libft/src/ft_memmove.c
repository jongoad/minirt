/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:13:20 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/23 10:13:11 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*src_ptr;
	unsigned char	*dest_ptr;

	src_ptr = (unsigned char *)src;
	dest_ptr = (unsigned char *)dest;
	if (src == dest)
		return (NULL);
	if (dest > src)
	{
		while (len--)
			*(dest_ptr + len) = *(src_ptr + len);
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
