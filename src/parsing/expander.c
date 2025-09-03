/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/09/01 20:19:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

int	found(char *var, char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i])
	{
		if (env_var[i] == '=')
		{
			if (var[i] == '\0')
				return (1);
			else
				return (0);
		}
		if (env_var[i] != var[i])
			return (0);
		i++;
	}
	return (0);
}

char	*ft_getenvx(char *var, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (found(var, env[i]))
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			return (ft_strndup(env[i] + j + 1, ft_strlen(env[i]) - j - 1));
		}
		i++;
	}
	return (NULL);
}

static char	*expand_variable(
		char **temp, char **start, char *expanded, t_env *env)
{
	char	*var;
	char	*env_var;

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
	while (**temp && **temp != ' ' && **temp != '\t' && **temp != '\n'
		&& **temp != '"' && **temp != '$' && **temp != '\'')
		(*temp)++;
	var = ft_strndup(*start + 1, *temp - *start - 1);
	env_var = ft_getenvx(var, env->env);
	if (env_var)
		expanded = ft_strjoin(expanded, env_var);
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
		if (current->name)
			current->name = expand_word(current->name, env);
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
