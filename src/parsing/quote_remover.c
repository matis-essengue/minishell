/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:29 by messengu          #+#    #+#             */
/*   Updated: 2025/09/13 12:05:50 by messengu         ###   ########.fr       */
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
char	handle_quotes(
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
 * @brief Finalize the quote removal process
 *
 * @param new_word The partially built word
 * @param start Start of the remaining segment
 * @param end End of the string
 * @param word Original word to free
 * @return The final result
 */
char	*finalize_quote_removal(
	char *new_word,
	char *start,
	char *end,
	char *word)
{
	char	*dup;
	char	*res;

	dup = ft_strndup(start, end - start);
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
	return (res);
}

/**
 * @brief Process command name removal of quotes
 *
 * @param current The current command
 * @return 0 on success, 1 on failure
 */
static int	_process_cmd_name(t_cmd *current)
{
	char	*old_name;

	if (!current->name)
		return (0);
	old_name = current->name;
	current->name = _remove_quotes(current->name);
	if (!current->name)
	{
		current->name = old_name;
		return (1);
	}
	return (0);
}

/**
 * @brief Process arguments removal of quotes
 *
 * @param args The arguments array
 * @return 0 on success, 1 on failure
 */
static int	_process_args(char **args)
{
	int		i;
	char	*old_arg;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		old_arg = args[i];
		args[i] = _remove_quotes(args[i]);
		if (!args[i])
		{
			args[i] = old_arg;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Remove quotes from the commands
 *
 * @param cmds The list of commands
 */
void	remove_quotes(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (_process_cmd_name(current))
			return ;
		if (current->infile)
			rm_quotes_for_all_files(current->infile);
		if (current->outfile)
			rm_quotes_for_all_files(current->outfile);
		if (current->heredocs)
			rm_quotes_for_all_heredocs(current->heredocs);
		if (_process_args(current->args))
			return ;
		current = current->next;
	}
}
