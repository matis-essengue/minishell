/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:04 by messengu          #+#    #+#             */
/*   Updated: 2025/06/16 16:46:20 by armosnie         ###   ########.fr       */
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
	// printf("\n\nEXPANDING TOKENS\n");
	current_cmd = cmds;
	expand_cmds(current_cmd);
	current = tokens;
	while (current != NULL)
	{
		printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
		current = current->next;
	}
	// printf("REMOVING QUOTES\n");
	current_cmd = cmds;
	remove_quotes(current_cmd);
	current = tokens;
	while (current != NULL)
	{
		printf("token [%s]: %s\n", get_token_type_str(current->type), current->value);
		current = current->next;
	}

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
	// current_cmd = cmds;
	// while (current_cmd != NULL)
	// {
	// 	printf("test\n");
	// 	if (current_cmd->output_type == HERE_DOC)
	// 	{
	// 		manage_heredoc()
	// 	}
	// 	else
	// 	{
	// 		t_file *current_file;
	// 		current_file = current_cmd->outfile;
	// 		while (current_file != NULL)
	// 		{
	// 			if (current_file != NULL)
	// 				close(current_file);
	// 			ft_open(current_file->name, current_file->permission);
	// 			current_file = current_file->next;
	// 		}
	// 		// outfile = 
	// 	}
	// 	current_cmd = current_cmd->next;
	// }
	free(tokens);
	return (cmds);
}

