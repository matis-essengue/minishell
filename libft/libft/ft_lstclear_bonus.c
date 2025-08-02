/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:43:28 by matis             #+#    #+#             */
/*   Updated: 2024/11/26 11:31:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_elem;

	while (*lst)
	{
		next_elem = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next_elem;
	}
	*lst = NULL;
}

// #include <string.h>

// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*node1;
// 	t_list	*node2;

// 	node1 = ft_lstnew(strdup("Node 1"));
// 	node2 = ft_lstnew(strdup("Node 2"));
// 	head = node1;
// 	node1->next = node2;

// 	printf("Before clear: head -> [%s], next -> [%s]\n",
//		(char *)head->content, (char *)head->next->content);
// 	ft_lstclear(&head, del);
// 	printf("After clear: head -> [%p]\n", (void *)head);

// 	return (0);
// }
