/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:31:23 by messengu          #+#    #+#             */
/*   Updated: 2024/11/26 11:30:46 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*scpy;

	i = 0;
	scpy = (unsigned char *)s;
	while (i < n)
	{
		if (scpy[i] == (unsigned char)c)
			return ((void *)&scpy[i]);
		i++;
	}
	return (NULL);
}

// #include <string.h>

// int	main(void)
// {
// 	const char	str[] = "Hello, world!";
// 	void		*result_ft;
// 	void		*result_std;

// 	// Test 1 : Caractère trouvé dans une chaîne normale
// 	result_ft = ft_memchr(str, 'o', strlen(str));
// 	result_std = memchr(str, 'o', strlen(str));
// 	printf("Test 1: ft_memchr -> [%s], memchr -> [%s]\n",
// 		(char *)result_ft, (char *)result_std);

// 	// Test 2 : Caractère non trouvé
// 	result_ft = ft_memchr(str, 'z', strlen(str));
// 	result_std = memchr(str, 'z', strlen(str));
// 	printf("Test 2: ft_memchr -> [%p], memchr -> [%p]\n",
//		result_ft, result_std);

// 	// Test 3 : Recherche du premier caractère
// 	result_ft = ft_memchr(str, 'H', strlen(str));
// 	result_std = memchr(str, 'H', strlen(str));
// 	printf("Test 3: ft_memchr -> [%s], memchr -> [%s]\n",
// 		(char *)result_ft, (char *)result_std);

// 	// Test 4 : Recherche du dernier caractère
// 	result_ft = ft_memchr(str, '!', strlen(str));
// 	result_std = memchr(str, '!', strlen(str));
// 	printf("Test 4: ft_memchr -> [%s], memchr -> [%s]\n",
// 		(char *)result_ft, (char *)result_std);

// 	// Test 5 : Taille de recherche limitée (ne trouve pas le caractère)
// 	result_ft = ft_memchr(str, 'o', 5);
// 	result_std = memchr(str, 'o', 5);
// 	printf("Test 5: ft_memchr -> [%p], memchr -> [%p]\n",
//		result_ft, result_std);

// 	// Test 6 : Recherche dans une chaîne vide
// 	result_ft = ft_memchr("", 'a', 0);
// 	result_std = memchr("", 'a', 0);
// 	printf("Test 6: ft_memchr -> [%p], memchr -> [%p]\n",
//		result_ft, result_std);

// 	return (0);
// }
