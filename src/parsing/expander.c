/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 12:33:48 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*expand_word(char *word)
{
	char	*expanded;
	char	*temp;
	char	*start;
	int		squoted;

	temp = word;
	expanded = ft_strdup("");
	squoted = 0;
	start = word;
	while (*temp)
	{
		if (*temp == '\'')
			squoted = !squoted;
		if (*temp == '$' && !squoted)
		{
			if (*(temp + 1) && *(temp + 1) == '\"')
			{
				temp++;
				continue;
			}
			expanded = ft_strjoin(expanded, ft_strndup(start, temp - start));
			start = temp;
			temp++;
			while (*temp && *temp != ' ' && *temp != '\t' && *temp != '\n' && *temp != '"' && *temp != '$' && *temp != '\'')
				temp++;
			if (getenv(ft_strndup(start + 1, temp - start - 1)) != NULL)
				expanded = ft_strjoin(expanded, getenv(ft_strndup(start + 1, temp - start - 1)));
			start = temp;
		}
		else
			temp++;
	}
	expanded = ft_strjoin(expanded, ft_strndup(start, temp - start));
	return (expanded);
}

void	expand_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			current->value = expand_word(current->value);
		current = current->next;
	}
}
