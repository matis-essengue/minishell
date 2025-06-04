/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:06:51 by messengu          #+#    #+#             */
/*   Updated: 2024/11/26 10:10:41 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// #include <string.h>

// int	main(void)
// {
// 	char buffer1[20] = "Hello, world!";
// 	char buffer2[20] = "Hello, world!";

// 	// Test 1 : Remplir 5 premiers octets
// 	ft_bzero(buffer1, 5);
// 	bzero(buffer2, 5);

// 	printf("Test 1:\n");
// 	printf("Mon ft_bzero : [%s]\n", buffer1);
// 	printf("Fonction bzero : [%s]\n", buffer2);
// 	if (memcmp(buffer1, buffer2, 20) == 0)
// 		printf("Résultat : OK\n");
// 	else
// 		printf("Résultat : ÉCHEC\n");

// 	// Test 2 : Remplir toute la zone
// 	ft_bzero(buffer1, 20);
// 	bzero(buffer2, 20);

// 	printf("\nTest 2:\n");
// 	printf("Mon ft_bzero : [%s]\n", buffer1);
// 	printf("Fonction bzero : [%s]\n", buffer2);
// 	if (memcmp(buffer1, buffer2, 20) == 0)
// 		printf("Résultat : OK\n");
// 	else
// 		printf("Résultat : ÉCHEC\n");

// 	// Test 3 : Remplir avec n = 0 (ne devrait rien changer)
// 	char buffer3[20] = "Hello, world!";
// 	ft_bzero(buffer3, 0);

// 	printf("\nTest 3:\n");
// 	printf("Mon ft_bzero avec n = 0 : [%s]\n", buffer3);
// 	if (strcmp(buffer3, "Hello, world!") == 0)
// 		printf("Résultat : OK\n");
// 	else
// 		printf("Résultat : ÉCHEC\n");

// 	return (0);
// }
