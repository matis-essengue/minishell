/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:04 by messengu          #+#    #+#             */
/*   Updated: 2025/09/09 16:07:58 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	debug_cmds(t_cmd *current_cmd)
{
	int	j;

	printf("\n\033[32mPARSED COMMANDS\033[0m\n");
	j = 1;
	while (current_cmd != NULL)
	{
		printf("\033[32mcmd %d:\033[0m\n", j);
		print_cmd(current_cmd);
		current_cmd = current_cmd->next;
		j++;
	}
}

t_cmd	*parse(char *line, t_env *env)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmds;
	(void)env;

	expand_line(&line, env);
	tokens = tokenize(line);
	free(line);
	if (!tokens)
		return (NULL);
	current = tokens;
	if (!check_tokens(current))
	{
		env->exit_status = 258;
		return (NULL);
	}
	cmds = tokens_to_cmds(tokens);
	free_tokens(tokens);
	remove_quotes(cmds);
	debug_cmds(cmds);
	return (cmds);
}
