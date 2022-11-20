/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:52:51 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/08 19:52:52 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief This function prints elements of a 2D char array with a prefix 
 * on each line represented by the variable name
 * USES PRINTF
 * 
 * @param split_arr	The string vector
 * @param name 		The name of the vector to be displayed
 */
void	ft_print_split(char **split_arr, char *name)
{
	int	i;

	i = 0;
	if (!split_arr)
		return ;
	while (split_arr[i])
	{
		printf("{%s} split_arr[%d] = \"%s\"\n", name, i, split_arr[i]);
		i++;
	}
	printf("{%s} null-terminated ?: %s\n", name, split_arr[i]);
	return ;
}
