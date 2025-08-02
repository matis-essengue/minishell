/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:10:32 by messengu          #+#    #+#             */
/*   Updated: 2024/11/25 23:53:33 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_size;

	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	needle_size = ft_strlen(needle);
	while (haystack[i] && i + needle_size <= len)
	{
		if (ft_strncmp(&haystack[i], needle, needle_size) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
