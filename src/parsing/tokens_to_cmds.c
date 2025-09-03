/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:12:25 by messengu          #+#    #+#             */
/*   Updated: 2025/09/03 11:13:13 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	cmd->exit_status = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	cmd->output_type = STDOUT;
	cmd->input_type = STDIN;
	cmd->heredocs = NULL;
}

static void	process_cmd_name_and_count_args(t_cmd *cmd,
	t_token *tokens, int *arg_count)
{
	t_token	*current;

	*arg_count = 0;
	current = tokens;
	while (current && current->type != TOKEN_CONTROL_OP)
	{
		if (current->type == TOKEN_WORD)
		{
			if (cmd->name == NULL)
				cmd->name = ft_strdup(current->value);
			else
				(*arg_count)++;
		}
		else
			current = current->next;
		current = current->next;
	}
}

static t_cmd	*handle_pipe(t_cmd *cmds)
{
	cmds->next = malloc(sizeof(t_cmd));
	cmds->output_type = PIPEOUT;
	init_cmd(cmds->next);
	cmds = cmds->next;
	cmds->input_type = PIPEIN;
	return (cmds);
}

static t_token	*process_command(t_cmd *cmd,
	t_token **tokens, t_file **start_infile, t_file **start_outfile)
{
	t_token	*start;
	int		arg_count;

	start = *tokens;
	process_cmd_name_and_count_args(cmd, *tokens, &arg_count);
	allocate_and_fill_args(cmd, start, arg_count);
	process_redirections(cmd, start, start_infile, start_outfile);
	reset_file_pointers(cmd, start_infile, start_outfile);
	while (*tokens && (*tokens)->type != TOKEN_CONTROL_OP)
		*tokens = (*tokens)->next;
	return (*tokens);
}

t_cmd	*tokens_to_cmds(t_token *tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*cmds;
	t_token	*current;
	t_file	*start_infile;
	t_file	*start_outfile;

	cmds = malloc(sizeof(t_cmd));
	init_cmd(cmds);
	first_cmd = cmds;
	current = tokens;
	start_infile = NULL;
	start_outfile = NULL;
	while (current)
	{
		if (current->type != TOKEN_CONTROL_OP)
			process_command(cmds, &current, &start_infile, &start_outfile);
		if (current && current->type == TOKEN_CONTROL_OP)
		{
			cmds = handle_pipe(cmds);
			current = current->next;
		}
	}
	return (first_cmd);
}
