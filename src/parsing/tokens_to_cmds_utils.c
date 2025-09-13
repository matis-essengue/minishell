/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:12:25 by messengu          #+#    #+#             */
/*   Updated: 2025/09/09 21:24:10 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

static int	fill_args_array(t_cmd *cmd, t_token *tokens)
{
	t_token	*current;
	int		i;

	i = -1;
	current = tokens;
	while (current && current->type != TOKEN_CONTROL_OP)
	{
		if (current->type == TOKEN_WORD)
		{
			if (i >= 0)
			{
				cmd->args[i] = ft_strdup(current->value);
				if (!cmd->args[i])
					return (-1);
			}
			i++;
		}
		else
			current = current->next;
		current = current->next;
	}
	return (i);
}

void	allocate_and_fill_args(t_cmd *cmd, t_token *tokens, int arg_count)
{
	int	i;

	if (arg_count == 0)
		return ;
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return ;
	i = fill_args_array(cmd, tokens);
	if (i >= 0)
		cmd->args[i] = NULL;
}

static void	handle_heredoc(t_cmd *cmd, t_token *current)
{
	t_heredoc	*heredoc;
	t_heredoc	*tmp;

	heredoc = malloc(sizeof(t_heredoc));
	heredoc->delimiter = ft_strdup(current->next->value);
	heredoc->content = NULL;
	heredoc->heredoc_fd = -1;
	heredoc->next = NULL;
	cmd->input_type = HERE_DOC;
	if (cmd->heredocs == NULL)
		cmd->heredocs = heredoc;
	else
	{
		tmp = cmd->heredocs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = heredoc;
	}
}

t_token	*process_redirections(t_cmd *cmd,
	t_token *tokens, t_file **start_infile, t_file **start_outfile)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != TOKEN_CONTROL_OP)
	{
		if (current->type == TOKEN_REDIRECT_OP)
		{
			if (ft_strncmp(current->value, ">>", 2) == 0
				|| ft_strncmp(current->value, ">", 1) == 0)
				handle_output_redirect(cmd, current, start_outfile);
			else if (ft_strncmp(current->value, "<<", 2) == 0)
				handle_heredoc(cmd, current);
			else if (ft_strncmp(current->value, "<", 1) == 0)
				handle_input_redirect(cmd, current, start_infile);
			else
				continue ;
			current = current->next;
		}
		current = current->next;
	}
	return (current);
}

void	reset_file_pointers(t_cmd *cmd,
	t_file **start_infile, t_file **start_outfile)
{
	if (*start_infile)
	{
		cmd->infile = *start_infile;
		*start_infile = NULL;
	}
	if (*start_outfile)
	{
		cmd->outfile = *start_outfile;
		*start_outfile = NULL;
	}
}
