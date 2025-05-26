/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:40:19 by matis             #+#    #+#             */
/*   Updated: 2024/11/26 10:26:34 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	if (n < 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		sign;
	char	*res;

	len = n_len(n);
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = n % 10 * sign + '0';
		n /= 10;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}

// #include <limits.h>

// int	main(void)
// {
// 	char	*result;

// 	// Test 1 : Conversion d'un entier positif
// 	result = ft_itoa(12345);
// 	printf("Test 1: ft_itoa(12345) -> [%s]\n", result);
// 	free(result);

// 	// Test 2 : Conversion d'un entier négatif
// 	result = ft_itoa(-12345);
// 	printf("Test 2: ft_itoa(-12345) -> [%s]\n", result);
// 	free(result);

// 	// Test 3 : Conversion de zéro
// 	result = ft_itoa(0);
// 	printf("Test 3: ft_itoa(0) -> [%s]\n", result);
// 	free(result);

// 	// Test 4 : Cas limite avec INT_MAX
// 	result = ft_itoa(INT_MAX);
// 	printf("Test 4: ft_itoa(INT_MAX) -> [%s]\n", result);
// 	free(result);

// 	// Test 5 : Cas limite avec INT_MIN
// 	result = ft_itoa(INT_MIN);
// 	printf("Test 5: ft_itoa(INT_MIN) -> [%s]\n", result);
// 	free(result);

// 	return (0);
// }
