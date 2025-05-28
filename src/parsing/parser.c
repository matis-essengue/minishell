/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:04 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 15:50:29 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
}

t_cmd	*parse_cmd(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*first_cmd;
	t_token	*current;
	t_token	*temp;
	int		arg_count;
	int		i;

	cmds = malloc(sizeof(t_cmd));
	first_cmd = cmds;
	init_cmd(cmds);
	current = tokens;
	temp = NULL;
	arg_count = 0;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			if (cmds->name == NULL)
			{
				cmds->name = current->value;
				temp = NULL;
			}
			else
			{
				if (*(current->value))
				{
					arg_count++;
					if (temp == NULL)
						temp = current;
				}
			}
		}
		else
		{
			if (arg_count)
			{
				cmds->args = malloc(sizeof(char *) * (arg_count + 1));
				i = 0;
				while (temp != current)
				{
					if (temp->value != NULL)
					{
						cmds->args[i] = temp->value;
						i++;
					}
					temp = temp->next;
				}
				cmds->args[i] = NULL;
				arg_count = 0;
			}
			if (cmds->name != NULL)
			{
				cmds->next = malloc(sizeof(t_cmd));
				init_cmd(cmds->next);
				cmds = cmds->next;
			}
		}
		current = current->next;
	}
	if (arg_count)
	{
		cmds->args = malloc(sizeof(char *) * (arg_count + 1));
		i = 0;
		while (i < arg_count)
		{
			if (temp->value != NULL)
			{
				cmds->args[i] = temp->value;
				i++;
			}
			temp = temp->next;
		}
		cmds->args[i] = NULL;
	}
	return (first_cmd);
}


int	parse(char *line)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmds;
	t_cmd	*current_cmd;

	// printf("line: %s\n", line);
	tokens = tokenize(line);
	if (!tokens)
		return (1);
	// current = tokens;
	// while (current != NULL)
	// {
	// 	printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
	// 	current = current->next;
	// }
	current = tokens;
	if (!check_tokens(current))
		return (1);
	// printf("\n\nEXPANDING TOKENS\n");
	current = tokens;
	expand_tokens(current);
	// current = tokens;
	// while (current != NULL)
	// {
	// 	printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
	// 	current = current->next;
	// }
	// printf("REMOVING QUOTES\n");
	current = tokens;
	remove_quotes(current);
	// current = tokens;
	// while (current != NULL)
	// {
	// 	printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
	// 	current = current->next;
	// }

	// printf("PARSED COMMANDS\n");
	cmds = parse_cmd(tokens);
	current_cmd = cmds;
	int j = 1;
	while (current_cmd != NULL)
	{
		printf("cmd %d: ", j);
		print_cmd(current_cmd);
		current_cmd = current_cmd->next;
		j++;
	}

	check_cmds(cmds);
	free(tokens);
	return (0);
}

