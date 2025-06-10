/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:04 by messengu          #+#    #+#             */
/*   Updated: 2025/06/10 18:46:48 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

t_cmd	*parse(char *line)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmds;
	t_cmd	*current_cmd;

	// printf("line: %s\n", line);
	tokens = tokenize(line);
	if (!tokens)
		return (NULL);
	// current = tokens;
	// while (current != NULL)
	// {
	// 	printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
	// 	current = current->next;
	// }
	current = tokens;
	if (!check_tokens(current))
		return (NULL);

	cmds = tokens_to_cmds(tokens);
	current_cmd = cmds;
	expand_cmds(cmds);
	remove_quotes(cmds);

	printf("\n\033[32mPARSED COMMANDS\033[0m\n");
	current_cmd = cmds;
	int j = 1;
	while (current_cmd != NULL)
	{
		printf("\033[32mcmd %d:\033[0m\n", j);
		print_cmd(current_cmd);
		current_cmd = current_cmd->next;
		j++;
	}

	// check_cmds(cmds);
	free(tokens);
	return (cmds);
}

