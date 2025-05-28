/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:33:04 by messengu          #+#    #+#             */
/*   Updated: 2025/05/27 16:56:47 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*ft_strndup(const char *s1, int n)
{
	int		strlen;
	char	*dup;

	strlen = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * n + 1);
	if (!dup)
		return (NULL);
	strlen = 0;
	while (s1[strlen] && strlen < n)
	{
		dup[strlen] = s1[strlen];
		strlen++;
	}
	dup[strlen] = '\0';
	return (dup);
}
