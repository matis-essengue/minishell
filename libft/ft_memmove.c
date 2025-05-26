/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:58:54 by messengu          #+#    #+#             */
/*   Updated: 2024/11/26 00:04:03 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (cdest == csrc)
		return (dest);
	if (cdest > csrc)
	{
		while (n--)
			*(cdest + n) = *(csrc + n);
		return (dest);
	}
	while (n--)
		*cdest++ = *csrc++;
	return (dest);
}
