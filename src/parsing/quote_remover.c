/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:29 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 18:37:07 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/**
 * @brief Handle quote detection and processing
 *
 * @param temp Current character pointer
 * @param quote Current quote state
 * @param start Start of the current segment
 * @param new_word The word being built
 * @return The updated quote state
 */
static char	_handle_quotes(
	char *temp,
	char quote,
	char **start,
	char **new_word)
{
	if (!quote)
		quote = *temp;
	else if (quote == *temp)
		quote = 0;
	else if (quote != *temp)
		return (quote);
	*new_word = ft_strjoin(*new_word, ft_strndup(*start, temp - *start));
	*start = temp + 1;
	return (quote);
}

/**
 * @brief Remove quotes from a word
 *
 * @param word The word to remove quotes from
 * @return The word without quotes
 */
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
			quote = _handle_quotes(temp, quote, &start, &new_word);
		temp++;
	}
	new_word = ft_strjoin(new_word, ft_strndup(start, temp - start));
	return (new_word);
}

/**
 * @brief Remove quotes from the tokens
 *
 * @param tokens The list of tokens
 */
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
