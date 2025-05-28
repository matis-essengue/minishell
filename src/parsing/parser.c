/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:04 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 12:24:49 by messengu         ###   ########.fr       */
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
				arg_count++;
				if (temp == NULL)
					temp = current;
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
					cmds->args[i] = temp->value;
					i++;
					temp = temp->next;
				}
				printf("\n");
				cmds->args[i] = NULL;
				arg_count = 0;
			}
			cmds->next = malloc(sizeof(t_cmd));
			init_cmd(cmds->next);
			cmds = cmds->next;
		}
		current = current->next;
	}
	if (arg_count)
	{
		cmds->args = malloc(sizeof(char *) * (arg_count + 1));
		i = 0;
		while (i < arg_count)
		{
			cmds->args[i] = temp->value;
			i++;
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

	printf("line: %s\n", line);
	tokens = tokenize(line);
	if (!tokens)
		return (1);
	current = tokens;
	while (current != NULL)
	{
		printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
		current = current->next;
	}
	current = tokens;
	check_tokens(current);
	printf("\n\nEXPANDING TOKENS\n");
	current = tokens;
	expand_tokens(current);
	current = tokens;
	while (current != NULL)
	{
		printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
		current = current->next;
	}
	printf("\n\nREMOVING QUOTES\n");
	current = tokens;
	remove_quotes(current);
	current = tokens;
	while (current != NULL)
	{
		printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
		current = current->next;
	}

	cmds = parse_cmd(tokens);
	current_cmd = cmds;
	int i;
	int j = 1;
	while (current_cmd != NULL)
	{
		printf("cmd %d: %s", j, current_cmd->name);
		i = 0;
		while (current_cmd->args[i] != NULL)
		{
			printf(" %s", current_cmd->args[i]);
			i++;
			if (i >= 10)
				break;
		}
		printf("\n");
		current_cmd = current_cmd->next;
		j++;
	}
	free(tokens);
	return (0);
}

