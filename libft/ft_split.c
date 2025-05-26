/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:15:09 by matis             #+#    #+#             */
/*   Updated: 2025/04/24 21:13:11 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_end_of_word(const char *s, char c)
{
	if (*s != c && *(s + 1) && *(s + 1) == c)
		return (1);
	if (*s != c && !*(s + 1))
		return (1);
	return (0);
}

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	char	*str;

	count = 0;
	str = (char *)s;
	while (*str)
	{
		if (is_end_of_word(str, c))
			count++;
		str++;
	}
	return (count);
}

static size_t	word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*get_next_word(const char *s, char c, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len * sizeof(char) + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (*s && *s != c)
		word[i++] = *(s++);
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	len;
	size_t	i;

	split = malloc(count_words(s, c) * sizeof(char *) + sizeof(NULL));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		len = word_len(s, c);
		split[i++] = get_next_word(s, c, len);
		s += len;
	}
	split[i] = NULL;
	return (split);
}

// int main()
// {
// 	char *str = "Hello World";
// 	char **split = ft_split(str, ' ');
// 	for (int i = 0; split[i]; i++)
// 	{
// 		printf("%s\n", split[i]);
// 	}
// 	return 0;
// }
