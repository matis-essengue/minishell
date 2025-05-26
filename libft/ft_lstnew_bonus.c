/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:14:15 by matis             #+#    #+#             */
/*   Updated: 2024/11/26 11:29:42 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;

// 	// Test 1 : Création d'un nœud avec une chaîne de caractères
// 	node1 = ft_lstnew("Hello, world!");
// 	if (node1)
// 		printf("Test 1: content -> [%s], next -> [%p]\n",
//			(char *)node1->content, node1->next);
// 	else
// 		printf("Test 1: Failed to create node\n");

// 	// Test 2 : Création d'un nœud avec une valeur NULL
// 	node2 = ft_lstnew(NULL);
// 	if (node2)
// 		printf("Test 2: content -> [%p], next -> [%p]\n",
//			node2->content, node2->next);
// 	else
// 		printf("Test 2: Failed to create node\n");

// 	// Libération de la mémoire
// 	free(node1);
// 	free(node2);

// 	return (0);
// }
