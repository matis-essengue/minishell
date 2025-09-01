/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/09/01 16:50:40 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static char	*expand_variable(char **temp, char **start, char *expanded, t_env *env)
{
	if (*(*temp + 1) && *(*temp + 1) == '$')
	{
		(*temp)++;
		return (expanded);
	}
	if (*(*temp + 1) && *(*temp + 1) == '?')
	{
		// TODO: expand $?
		(*temp)++;
		(*temp)++;
		return (expanded);
	}
	expanded = ft_strjoin(expanded, ft_strndup(*start, *temp - *start));
	*start = *temp;
	(*temp)++;
	while (**temp && **temp != ' ' && **temp != '\t' && **temp != '\n' && **temp != '"' && **temp != '$' && **temp != '\'')
		(*temp)++;
	if (ft_getenv(ft_strndup(*start + 1, *temp - *start - 1), env->env) != NULL)
		expanded = ft_strjoin(expanded, ft_getenv(ft_strndup(*start + 1, *temp - *start - 1), env->env));
	*start = *temp;
	return (expanded);
}

char	*expand_word(char *word, t_env *env)
{
	char	*expanded;
	char	*temp;
	char	*start;
	int		squoted;
	int		dquoted;

	temp = word;
	expanded = ft_strdup("");
	squoted = 0;
	dquoted = 0;
	start = word;
	while (*temp)
	{
		if (*temp == '"' && !squoted)
			dquoted = !dquoted;
		if (*temp == '\'' && !dquoted)
			squoted = !squoted;
		if (*temp == '$' && !squoted)
			expanded = expand_variable(&temp, &start, expanded, env);
		else
			temp++;
	}
	expanded = ft_strjoin(expanded, ft_strndup(start, temp - start));
	return (expanded);
}

void	expand_cmds(t_cmd *tokens, t_env *env)
{
	t_cmd	*current;
	int		i;

	current = tokens;
	while (current)
	{
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				current->args[i] = expand_word(current->args[i], env);
				i++;
			}
		}
		current = current->next;
	}
}
