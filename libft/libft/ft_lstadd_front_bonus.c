/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:17:21 by matis             #+#    #+#             */
/*   Updated: 2024/11/26 11:31:11 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*node1;
// 	t_list	*node2;

// 	node1 = ft_lstnew("Node 1");
// 	node2 = ft_lstnew("Node 2");
// 	head = NULL;
// 	ft_lstadd_front(&head, node1);
// 	printf("Test 1: head -> [%s]\n", (char *)head->content);

// 	ft_lstadd_front(&head, node2);
// 	printf("Test 2: new head -> [%s], next -> [%s]\n",
//		(char *)head->content, (char *)head->next->content);

// 	free(node1);
// 	free(node2);

// 	return (0);
// }
