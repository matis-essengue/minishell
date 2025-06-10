/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:12:25 by messengu          #+#    #+#             */
/*   Updated: 2025/06/03 14:05:37 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"


void	init_cmd(t_cmd *cmd)
{
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	cmd->output_type = STDOUT;
	cmd->input_type = STDIN;
	cmd->heredocs = NULL;
}

t_cmd	*tokens_to_cmds(t_token *tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*cmds;
	// t_token	*temp;
	t_token	*current;
	t_token	*start;
	t_heredoc	*heredoc;
	int		i;
	int		arg_count;
	t_file	*start_infile;
	t_file	*start_outfile;

	cmds = malloc(sizeof(t_cmd));
	init_cmd(cmds);
	first_cmd = cmds;
	current = tokens;
	// start = current;
	i = 0;
	while (current)
	{
		if (current->type != TOKEN_CONTROL_OP)
		{
			// ADDING NAME AND COUNTING ARGS
			start = current;
			// printf("STARTING AT : %s\n", current->value);
			arg_count = 0;
			while (current && current->type != TOKEN_CONTROL_OP)
			{
				if (current->type == TOKEN_WORD)
				{
					if (cmds->name == NULL)
						cmds->name = current->value;
					else
						arg_count++;
				}
				else
					current = current->next;
				current = current->next;
			}

			// ADDING ARGS
			if (arg_count != 0)
			{
				cmds->args = malloc(sizeof(char *) * (arg_count + 1));
				i = -1;
				current = start;
				// printf("STARTING AT : %s\n", current->value);
				while (current && current->type != TOKEN_CONTROL_OP)
				{
					if (current->type == TOKEN_WORD)
					{
						if (i >= 0)
							cmds->args[i] = current->value;
						i++;
					}
					else
						current = current->next;
					current = current->next;
				}
				cmds->args[i] = NULL;
			}

			// ADDING INFILE, OUTFILE AND HEREDOC
			current = start;
			// printf("STARTING AT : %s\n", current->value);
			while (current && current->type != TOKEN_CONTROL_OP)
			{
				// printf("CURRENT : %s\n", current->value);
				if (current->type == TOKEN_REDIRECT_OP)
				{
					// printf("REDIRECT_OP : %s\n", current->value);
					if (ft_strncmp(current->value, ">>", 2) == 0)
					{
						if (cmds->outfile == NULL)
						{
							cmds->outfile = malloc(sizeof(t_file));
							start_outfile = cmds->outfile;
						}
						else
						{
							cmds->outfile->next = malloc(sizeof(t_file));
							cmds->outfile = cmds->outfile->next;
						}
						cmds->outfile->name = current->next->value;
						cmds->outfile->permission[0] = '2';
						cmds->outfile->permission[1] = '2';
						cmds->outfile->permission[2] = '2';
						cmds->outfile->append = 1;
						cmds->outfile->next = NULL;
						current = current->next;
					}
					else if (ft_strncmp(current->value, "<<", 2) == 0)
					{
						heredoc = malloc(sizeof(t_heredoc));
						heredoc->delimiter = current->next->value;
						heredoc->content = NULL;
						heredoc->expand_vars = 1;
						heredoc->next = NULL;
						cmds->input_type = HERE_DOC;
						if (cmds->heredocs == NULL)
							cmds->heredocs = heredoc;
						else
						{
							heredoc->next = cmds->heredocs;
							cmds->heredocs = heredoc;
						}
						current = current->next;
					}
					else if (ft_strncmp(current->value, "<", 1) == 0)
					{
						// printf("INFILE\n");
						if (cmds->infile == NULL)
						{
							cmds->infile = malloc(sizeof(t_file));
							start_infile = cmds->infile;
						}
						else
						{
							cmds->infile->next = malloc(sizeof(t_file));
							cmds->infile = cmds->infile->next;
						}
						cmds->infile->name = current->next->value;
						cmds->infile->permission[0] = '4';
						cmds->infile->permission[1] = '4';
						cmds->infile->permission[2] = '4';
						cmds->infile->append = 0;
						cmds->infile->next = NULL;
						current = current->next;
					}
					else if (ft_strncmp(current->value, ">", 1) == 0)
					{
						if (cmds->outfile == NULL)
						{
							cmds->outfile = malloc(sizeof(t_file));
							start_outfile = cmds->outfile;
						}
						else
						{
							cmds->outfile->next = malloc(sizeof(t_file));
							cmds->outfile = cmds->outfile->next;
						}
						cmds->outfile->name = current->next->value;
						cmds->outfile->permission[0] = '2';
						cmds->outfile->permission[1] = '2';
						cmds->outfile->permission[2] = '2';
						cmds->outfile->append = 0;
						cmds->outfile->next = NULL;
						current = current->next;
					}
				}
				current = current->next;
			}
		}

		if (current && current->type == TOKEN_CONTROL_OP)
		{
			i = 0;
			cmds->next = malloc(sizeof(t_cmd));
			cmds->output_type = PIPEOUT;
			init_cmd(cmds->next);
			cmds = cmds->next;
			cmds->input_type = PIPEIN;
		}

		if (current)
			current = current->next;
	}
	if (cmds->infile)
		cmds->infile = start_infile;
	if (cmds->outfile)
		cmds->outfile = start_outfile;
	return (first_cmd);
}
