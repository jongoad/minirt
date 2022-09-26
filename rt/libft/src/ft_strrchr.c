/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:19:44 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/22 14:59:32 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	needle;

	ptr = NULL;
	needle = (char) c;
	while (*s)
	{
		if (*s == needle)
			ptr = (char *) s;
		s++;
	}
	if (needle == '\0')
		return ((char *) s);
	return (ptr);
}
