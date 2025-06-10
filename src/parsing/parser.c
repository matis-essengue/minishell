/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:04 by messengu          #+#    #+#             */
/*   Updated: 2025/05/29 19:43:18 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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

	cmds = tokens_to_cmds(tokens);
	current_cmd = cmds;
	int j = 1;
	while (current_cmd != NULL)
	{
		printf("cmd %d:\n", j);
		print_cmd(current_cmd);
		current_cmd = current_cmd->next;
		j++;
	}
	// printf("\n\nEXPANDING TOKENS\n");
	// current_cmd = cmds;
	// expand_cmds(current_cmd);
	// current = tokens;
	// while (current != NULL)
	// {
	// 	printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
	// 	current = current->next;
	// }
	// printf("REMOVING QUOTES\n");
	// current_cmd = cmds;
	// remove_quotes(current_cmd);
	// current = tokens;
	// while (current != NULL)
	// {
	// 	printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
	// 	current = current->next;
	// }

	// printf("PARSED COMMANDS\n");
	// current_cmd = cmds;
	// j = 1;
	// while (current_cmd != NULL)
	// {
	// 	printf("cmd %d: ", j);
	// 	print_cmd(current_cmd);
	// 	current_cmd = current_cmd->next;
	// 	j++;
	// }

	// check_cmds(cmds);
	free(tokens);
	return (0);
}

