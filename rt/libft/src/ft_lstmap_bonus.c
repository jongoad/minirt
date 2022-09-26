/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:56:08 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/23 14:17:30 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_node;
	t_list	*node_buffer;

	if (!lst)
		return (NULL);
	first_node = ft_lstnew((*f)(lst->content));
	if (!first_node)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		node_buffer = ft_lstnew((*f)(lst->content));
		if (!node_buffer)
		{
			ft_lstclear(&first_node, del);
			return (NULL);
		}
		ft_lstadd_back(&first_node, node_buffer);
		lst = lst->next;
	}
	return (first_node);
}
