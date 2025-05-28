/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:29 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 11:36:53 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*_remove_quotes(char *word)
{
	char	*new_word;
	char	quote;
	char	*start;
	char	*temp;

	new_word = ft_strdup("");
	quote = 0;
	start = word;
	temp = word;
	while (*temp)
	{
		if (*temp == '\'' || *temp == '"')
		{
			if (!quote)
				quote = *temp;
			else if (quote == *temp)
				quote = 0;
			else if (quote != *temp)
				continue;
			new_word = ft_strjoin(new_word, ft_strndup(start, temp - start));
			start = temp + 1;
		}
		temp++;
	}
	new_word = ft_strjoin(new_word, ft_strndup(start, temp - start));
	return (new_word);
}

void	remove_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			current->value = _remove_quotes(current->value);
		current = current->next;
	}
}
