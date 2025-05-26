/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:56:21 by messengu          #+#    #+#             */
/*   Updated: 2024/11/25 20:48:18 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nullstr(void)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * 1);
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	ssize;

	ssize = ft_strlen(s);
	if (start >= ssize)
		return (nullstr());
	if (len > ssize - start)
		len = ssize - start;
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

// int main()
// {
// 	char *sub = ft_substr("hola", 0, -1);
// 	printf("%s\n", sub);
// 	return 0;
// }
