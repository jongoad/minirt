/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:55:33 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/22 14:55:36 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*buffer;

	if (lst && del)
	{
		ptr = *lst;
		while (ptr)
		{
			buffer = ptr->next;
			ft_lstdelone(ptr, del);
			ptr = buffer;
		}
	}
	*lst = NULL;
}
