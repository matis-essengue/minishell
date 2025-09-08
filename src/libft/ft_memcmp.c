/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:56:55 by messengu          #+#    #+#             */
/*   Updated: 2024/11/26 11:11:02 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const void	*s1cpy;
	const void	*s2cpy;

	s1cpy = s1;
	s2cpy = s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i++ < n - 1 && *(unsigned char *)s1cpy == *(unsigned char *)s2cpy)
	{
		s1cpy++;
		s2cpy++;
	}
	return (*(unsigned char *)s1cpy - *(unsigned char *)s2cpy);
}
