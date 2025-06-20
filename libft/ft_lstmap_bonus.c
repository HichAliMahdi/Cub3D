/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hali-mah <hali-mah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:50:53 by hali-mah          #+#    #+#             */
/*   Updated: 2024/10/11 13:07:04 by hali-mah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*n_node;
	void	*n_content;

	n_lst = NULL;
	while (lst != NULL)
	{
		n_content = f(lst->content);
		n_node = malloc(sizeof(t_list));
		if (n_node == NULL)
		{
			del (n_content);
			ft_lstclear(&n_lst, (*del));
			return (NULL);
		}
		n_node->content = n_content;
		n_node->next = NULL;
		ft_lstadd_back(&n_lst, n_node);
		lst = lst->next;
	}
	return (n_lst);
}
