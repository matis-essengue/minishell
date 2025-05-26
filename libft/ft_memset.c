/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:11:12 by messengu          #+#    #+#             */
/*   Updated: 2024/11/25 13:57:36 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_cpy;
	size_t			i;

	b_cpy = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		b_cpy[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// int main()
// {
// 	char str[50] = "Hello World!";
// 	printf("Before memset(): %s\n", str);
// 	ft_memset(str, '-', 5);
// 	printf("After memset(): %s\n", str);
// 	return 0;
// }
