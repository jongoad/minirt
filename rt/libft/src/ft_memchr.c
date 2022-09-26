/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:10:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/22 19:35:08 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	if (!n)
		return (NULL);
	while (--n)
	{
		if (*ptr == (unsigned char) c)
			return (ptr);
		ptr++;
	}
	if ((unsigned char) c == *ptr)
		return (ptr);
	return (NULL);
}
