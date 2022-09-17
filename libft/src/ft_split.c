/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:05:51 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/26 19:49:51 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char(char const s, char const c)
{
	if (s == c && c)
		return (1);
	return (0);
}

static size_t	get_chunk_len(char const *s, char c)
{
	size_t	len;

	if (!c)
		return (ft_strlen(s));
	len = 0;
	while (!is_char(s[len], c) && s[len])
		len++;
	return (len);
}

static size_t	get_nb_chunks(char const *s, char const c)
{
	size_t	nb_chunks;
	int		is_chunk;

	nb_chunks = 0;
	if (!*s)
		return (nb_chunks);
	if (!is_char(*s++, c))
		is_chunk = 1;
	while (*s)
	{
		if (!is_char(*s, c))
			is_chunk = 1;
		else
			is_chunk = 0;
		if (is_chunk == 0 && !is_char(*(s - 1), c))
			nb_chunks++;
		s++;
	}
	if (is_chunk == 1)
		nb_chunks++;
	return (nb_chunks);
}

void	ft_free_split(char **split_arr)
{
	int	i;

	i = 0;
	if (!split_arr)
		return ;
	while (split_arr[i])
		free(split_arr[i++]);
	free (split_arr);
	split_arr = NULL;
	return ;
}

char	**ft_split(char const *s, char const c)
{
	size_t	nb_chunks;
	char	**split_arr;
	size_t	i;
	size_t	chunk_len;

	i = 0;
	if (!s)
		return (NULL);
	nb_chunks = get_nb_chunks(s, c);
	split_arr = malloc((nb_chunks + 1) * sizeof(char *));
	if (!split_arr)
		return (NULL);
	while (i < nb_chunks)
	{
		while (is_char(*s, c))
			s++;
		chunk_len = get_chunk_len(s, c);
		split_arr[i] = ft_substr(s, 0, chunk_len);
		if (!split_arr[i])
			ft_free_split(split_arr);
		i++;
		s += chunk_len;
	}
	split_arr[i] = NULL;
	return (split_arr);
}
