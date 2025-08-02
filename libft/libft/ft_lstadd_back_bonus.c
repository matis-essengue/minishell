/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:31:21 by matis             #+#    #+#             */
/*   Updated: 2024/11/26 11:24:29 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	elem = *lst;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst = new;
}

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	node1 = ft_lstnew("Node 1");
// 	node2 = ft_lstnew("Node 2");
// 	node3 = ft_lstnew("Node 3");

// 	head = NULL;
// 	ft_lstadd_back(&head, node1);
// 	printf("Test 1: head -> [%s]\n", (char *)head->content);

// 	ft_lstadd_back(&head, node2);
// 	printf("Test 2: second node -> [%s]\n", (char *)head->next->content);

// 	ft_lstadd_back(&head, node3);
// 	printf("Test 3: third node -> [%s]\n", (char *)head->next->next->content);

// 	free(node1);
// 	free(node2);
// 	free(node3);

// 	return (0);
// }
