/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:33:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/17 16:30:48 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	search_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen_opti(char *str)
{
	char	*len;

	len = str;
	while (*len)
		len++;
	return (len - str);
}

char	*ft_strndup_gnl(char *str, char c)
{
	size_t	i;
	char	*dup;

	dup = malloc(ft_strlen(str) + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		if (str[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	dup[i] = '\0';
	return (dup);
}