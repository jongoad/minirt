/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:33:16 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/22 16:35:06 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	if (!n)
		return (0);
	while (n-- > 1)
	{
		if (*ptr1 != *ptr2)
			break ;
		ptr1++;
		ptr2++;
	}
	return (*ptr1 - *ptr2);
}
