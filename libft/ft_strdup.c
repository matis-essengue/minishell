/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:32:50 by messengu          #+#    #+#             */
/*   Updated: 2024/11/25 17:51:19 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		strlen;
	char	*dup;

	strlen = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * strlen + 1);
	if (!dup)
		return (NULL);
	strlen = 0;
	while (s1[strlen])
	{
		dup[strlen] = s1[strlen];
		strlen++;
	}
	dup[strlen] = '\0';
	return (dup);
}
