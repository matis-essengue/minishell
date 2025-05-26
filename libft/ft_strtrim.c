/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:25:21 by matis             #+#    #+#             */
/*   Updated: 2024/11/25 18:48:49 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(const char c, char const *set)
{
	char	*set_cpy;

	set_cpy = (char *)set;
	while (*set_cpy)
	{
		if (*set_cpy == c)
			return (1);
		set_cpy++;
	}
	return (0);
}

static size_t	get_len(const char *s1, char const *set)
{
	char	*s;
	size_t	len;

	len = 0;
	s = (char *)s1;
	while (*s && is_set(*s, set))
		s++;
	while (*s)
	{
		s++;
		len++;
	}
	if (len == 0)
		return (len);
	s--;
	while (is_set(*s, set))
	{
		s--;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*trimmed;
	char	*s;

	len = get_len(s1, set) + 1;
	trimmed = malloc(sizeof(char) * len);
	if (!trimmed)
		return (NULL);
	s = (char *)s1;
	while (is_set(*s, set))
		s++;
	ft_strlcpy(trimmed, s, len);
	return (trimmed);
}
