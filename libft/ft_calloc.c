/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:01:53 by messengu          #+#    #+#             */
/*   Updated: 2024/11/26 10:22:56 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	if (count != total_size / size)
		return (NULL);
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, total_size);
	return (ptr);
}

// #include <string.h>

// int	main(void)
// {
// 	void	*ptr1;
// 	void	*ptr2;
// 	size_t	count;
// 	size_t	size;

// 	// Test 1 : Allocation normale
// 	count = 5;
// 	size = sizeof(int);
// 	ptr1 = ft_calloc(count, size);
// 	ptr2 = calloc(count, size);

// 	printf("Test 1:\n");
// 	if (ptr1 && ptr2 && memcmp(ptr1, ptr2, count * size) == 0)
// 		printf("Résultat : OK (les zones mémoire sont identiques)\n");
// 	else
// 		printf("Résultat : ÉCHEC\n");

// 	free(ptr1);
// 	free(ptr2);

// 	// Test 2 : Détection d'overflow
// 	count = SIZE_MAX;
// 	size = 2;
// 	ptr1 = ft_calloc(count, size);
// 	ptr2 = calloc(count, size);

// 	printf("\nTest 2:\n");
// 	if (!ptr1 && !ptr2)
// 		printf("Résultat : OK (overflow détecté)\n");
// 	else
// 		printf("Résultat : ÉCHEC\n");

// 	free(ptr1);
// 	free(ptr2);

// 	return (0);
// }
