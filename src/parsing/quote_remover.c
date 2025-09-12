/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:29 by messengu          #+#    #+#             */
/*   Updated: 2025/09/11 14:30:15 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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
	char	*chunk;
	char	*joined;
	
	if (!quote)
		quote = *temp;
	else if (quote == *temp)
		quote = 0;
	else if (quote != *temp)
		return (quote);
	chunk = ft_strndup(*start, temp - *start);
	joined = ft_strjoin(*new_word, chunk);
	free(*new_word);
	free(chunk);
	*new_word = joined;
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
	char	*dup;
	char	*res;

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
	dup = ft_strndup(start, temp - start);
	if (!dup)
	{
		free(new_word);
		free(word);
		return (NULL);
	}
	res = ft_strjoin(new_word, dup);
	free(new_word);
	free(dup);
	free(word);
	if (!res)
		return (NULL);
	return (res);
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

/**
 * @brief Remove quotes from the commands
 *
 * @param cmds The list of commands
 */
void	remove_quotes(t_cmd *cmds)
{
	t_cmd	*current;
	int		i;

	current = cmds;
	while (current)
	{
		i = 0;
		if (current->name)
		{
			char *old_name = current->name;
			current->name = _remove_quotes(current->name);
			if (!current->name)
			{
				current->name = old_name;
				return ;
			}
		}
		if (current->infile)
			rm_quotes_for_all_files(current->infile);
		if (current->outfile)
			rm_quotes_for_all_files(current->outfile);
		if (current->heredocs)
			rm_quotes_for_all_heredocs(current->heredocs);
		if (current->args)
		{
			while (current->args[i])
			{
				char *old_arg = current->args[i];
				current->args[i] = _remove_quotes(current->args[i]);
				if (!current->args[i])
				{
					current->args[i] = old_arg;
					return ;
				}
				i++;
			}
		}
		current = current->next;
	}
}
