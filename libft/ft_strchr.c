/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:36:53 by messengu          #+#    #+#             */
/*   Updated: 2024/11/25 19:43:18 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*scpy;
	char		modc;

	modc = c % 128;
	scpy = s;
	while (*scpy)
	{
		if (*scpy == modc)
			return ((char *)scpy);
		scpy++;
	}
	if (*scpy == modc)
		return ((char *)scpy);
	return (NULL);
}
