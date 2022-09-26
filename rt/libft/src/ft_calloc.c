/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:47:04 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/23 10:12:37 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*count and size initialized to 1 to prevent ft_bzero from crashing*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*mem_alloc;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	mem_alloc = malloc(count * size);
	if (!mem_alloc)
		return (NULL);
	ft_bzero(mem_alloc, count * size);
	return (mem_alloc);
}
