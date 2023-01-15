/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_node_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:58:37 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:58:39 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_node_remove(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !(*lst) || !node)
		return (ERROR);
	if (node == *lst)
		*lst = node->next;
	else
	{
		tmp = *lst;
		while (tmp->next && tmp->next != node)
			tmp = tmp->next;
		if (tmp->next != node)
			return (ERROR);
		tmp->next = node->next;
	}
	ft_lstdelone(node, del);
	return (0);
}
