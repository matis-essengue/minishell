/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:42:31 by matis             #+#    #+#             */
/*   Updated: 2025/09/03 14:47:36 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	free_files(t_file *files)
{
	t_file	*current;

	current = files;
	while (current)
	{
		free(current->name);
		current = current->next;
	}
}

static void	free_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*current;

	current = heredocs;
	while (current)
	{
		free(current->delimiter);
		free(current->content);
		current = current->next;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		free(current->name);
		free_args(current->args);
		free_files(current->infile);
		free_files(current->outfile);
		free_heredocs(current->heredocs);
		current = current->next;
	}
	free(cmds);
}
