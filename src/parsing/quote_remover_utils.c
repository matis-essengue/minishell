/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:29 by messengu          #+#    #+#             */
/*   Updated: 2025/09/13 12:06:32 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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
			quote = handle_quotes(temp, quote, &start, &new_word);
		temp++;
	}
	return (finalize_quote_removal(new_word, start, temp, word));
}

void	rm_quotes_for_all_files(t_file *first_file)
{
	t_file	*current_file;
	char	*old_name;

	current_file = first_file;
	while (current_file)
	{
		old_name = current_file->name;
		current_file->name = _remove_quotes(current_file->name);
		if (!current_file->name)
		{
			current_file->name = old_name;
			return ;
		}
		current_file = current_file->next;
	}
}

void	rm_quotes_for_all_heredocs(t_heredoc *first_heredoc)
{
	t_heredoc	*current_heredoc;
	char		*old_delimiter;

	current_heredoc = first_heredoc;
	while (current_heredoc)
	{
		old_delimiter = current_heredoc->delimiter;
		current_heredoc->delimiter = _remove_quotes(current_heredoc->delimiter);
		if (!current_heredoc->delimiter)
		{
			current_heredoc->delimiter = old_delimiter;
			return ;
		}
		current_heredoc = current_heredoc->next;
	}
}
