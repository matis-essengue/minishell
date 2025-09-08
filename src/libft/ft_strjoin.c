/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:55:49 by messengu          #+#    #+#             */
/*   Updated: 2025/04/24 20:10:46 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, (char *)s1, size1 + 1);
	ft_strlcpy(joined + size1, (char *)s2, size2 + 1);
	return (joined);
}
