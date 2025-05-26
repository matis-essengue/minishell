/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:57:22 by messengu          #+#    #+#             */
/*   Updated: 2024/11/26 00:08:19 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*scpy;
	char	*last_occ;
	char	modc;

	modc = c % 128;
	scpy = (char *)s;
	last_occ = NULL;
	while (*scpy)
	{
		if (*scpy == modc)
			last_occ = scpy;
		scpy++;
	}
	if (*scpy == modc)
		last_occ = scpy;
	return (last_occ);
}
