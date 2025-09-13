/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:12:25 by messengu          #+#    #+#             */
/*   Updated: 2025/09/13 12:02:51 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

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
	if (!cmds->next)
		return (NULL);
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

static t_cmd	*process_tokens_loop(t_cmd *cmds, t_token *tokens,
	t_file **start_infile, t_file **start_outfile)
{
	t_cmd	*first_cmd;
	t_token	*current;

	first_cmd = cmds;
	current = tokens;
	while (current)
	{
		if (current->type != TOKEN_CONTROL_OP)
			process_command(cmds, &current, start_infile, start_outfile);
		if (current && current->type == TOKEN_CONTROL_OP)
		{
			cmds = handle_pipe(cmds);
			if (!cmds)
			{
				free_all_struct(first_cmd);
				return (NULL);
			}
			current = current->next;
		}
	}
	return (first_cmd);
}

t_cmd	*tokens_to_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	t_file	*start_infile;
	t_file	*start_outfile;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	init_cmd(cmds);
	start_infile = NULL;
	start_outfile = NULL;
	return (process_tokens_loop(cmds, tokens, &start_infile, &start_outfile));
}
