/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:31:04 by messengu          #+#    #+#             */
/*   Updated: 2025/09/13 12:04:01 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

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
		free_tokens(tokens);
		return (NULL);
	}
	cmds = tokens_to_cmds(tokens);
	free_tokens(tokens);
	if (!cmds)
		return (NULL);
	remove_quotes(cmds);
	return (cmds);
}
