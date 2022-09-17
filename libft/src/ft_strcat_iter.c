/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_iter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:56:11 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 20:17:16 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_strcat_iter() assumes that vector is populated by malloced strings
 * If the vector has not been malloced, a free() error will occur. 
 * If the vector is NULL, nothing will happen
 * 
 * @param vector	The strings vector
 * @param to_cat 	The string to be concatenated on every element
 */
void	ft_strcat_iter(char **vector, char *to_cat)
{
	int	i;

	i = 0;
	while (vector && to_cat && vector[i])
	{
		vector[i] = ft_strjoin_free(vector[i], to_cat);
		if (!vector[i])
		{
			ft_free_split(vector);
			*vector = NULL;
			return ;
		}
		i++;
	}
	return ;
}
