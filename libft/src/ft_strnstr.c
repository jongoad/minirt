/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:26:51 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/22 14:59:42 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;

	if (*needle == 0)
		return ((char *) haystack);
	while (len-- && *haystack)
	{
		i = 0;
		while (needle[i] == haystack[i] && needle[i] && len - i + 1)
			i++;
		if (needle[i] == 0)
			return ((char *) haystack);
		haystack++;
	}
	return (NULL);
}
