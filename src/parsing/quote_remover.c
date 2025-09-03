/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:29 by messengu          #+#    #+#             */
/*   Updated: 2025/09/03 16:49:48 by matis            ###   ########.fr       */
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

void	rm_quotes_for_all_files(t_file *first_file)
{
	t_file	*current_file;

	current_file = first_file;
	while (current_file)
	{
		current_file->name = _remove_quotes(current_file->name);
		current_file = current_file->next;
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
			current->name = _remove_quotes(current->name);
		if (current->infile)
			rm_quotes_for_all_files(current->infile);
		if (current->outfile)
			rm_quotes_for_all_files(current->outfile);
		if (current->args)
		{
			while (current->args[i])
			{
				current->args[i] = _remove_quotes(current->args[i]);
				i++;
			}
		}
		current = current->next;
	}
}
