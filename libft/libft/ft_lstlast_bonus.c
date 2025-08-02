/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:26:09 by matis             #+#    #+#             */
/*   Updated: 2024/11/26 11:28:17 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*elem;

	elem = lst;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
	}
	return (elem);
}

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;
// 	t_list	*last;

// 	// Création des nœuds
// 	node1 = ft_lstnew("Node 1");
// 	node2 = ft_lstnew("Node 2");
// 	node3 = ft_lstnew("Node 3");

// 	// Liaison des nœuds
// 	head = node1;
// 	node1->next = node2;
// 	node2->next = node3;

// 	// Test : Obtenir le dernier nœud
// 	last = ft_lstlast(head);
// 	printf("Last node: [%s]\n", (char *)last->content);

// 	// Libération de la mémoire
// 	free(node1);
// 	free(node2);
// 	free(node3);

// 	return (0);
// }
