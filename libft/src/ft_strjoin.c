/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:29:52 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 19:57:26 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	tot_len;
	char	*s_joined;

	if (!s1 || !s2)
		return (NULL);
	tot_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s_joined = malloc(tot_len);
	if (!s_joined)
		return (NULL);
	while (*s1)
		*s_joined++ = *s1++;
	while (*s2)
		*s_joined++ = *s2++;
	*s_joined++ = 0;
	return (s_joined - tot_len);
}

char	*ft_strjoin_n(size_t nb_strings, ...)
{
	va_list	ap;
	size_t	i;
	char	*joined;

	i = 0;
	va_start(ap, nb_strings);
	joined = ft_strdup(va_arg(ap, char *));
	i++;
	while (i < nb_strings)
	{
		joined = ft_strjoin_free(joined, va_arg(ap, char *));
		i++;
	}
	va_end(ap);
	return (joined);
}
