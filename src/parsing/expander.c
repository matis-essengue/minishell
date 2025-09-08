/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/09/08 13:01:56 by matis            ###   ########.fr       */
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

static char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
		i++;
	var_name = ft_strndup(str, i);
	return (var_name);
}

static char	*expand_variable(char *str, t_env *env, int *consumed)
{
	char	*var_name;
	char	*value;
	char	*exit_code_str;

	*consumed = 1;
	if (!str[1] || str[1] == ' ' || str[1] == '\t' || str[1] == '\n')
		return (ft_strdup("$"));
	if (str[1] == '?')
	{
		*consumed = 2;
		exit_code_str = ft_itoa(env->exit_status);
		return (exit_code_str);
	}
	if (str[1] == '$')
	{
		*consumed = 2;
		return (ft_strdup("$$"));
	}
	var_name = get_var_name(str + 1);
	*consumed = ft_strlen(var_name) + 1;
	value = ft_getenvx(var_name, env->env);
	free(var_name);
	if (value)
		return (value);
	return (ft_strdup(""));
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

void	expand_line(char **line, t_env *env)
{
	char	*result;
	char	*temp;
	char	*expanded;
	int		i;
	int		start;
	int		squoted;
	int		dquoted;
	int		consumed;

	result = ft_strdup("");
	squoted = 0;
	dquoted = 0;
	i = 0;
	start = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' && !dquoted)
			squoted = !squoted;
		else if ((*line)[i] == '"' && !squoted)
			dquoted = !dquoted;
		else if ((*line)[i] == '$' && !squoted)
		{
			if (i > start)
			{
				temp = ft_strndup(*line + start, i - start);
				result = join_and_free(result, temp);
			}
			expanded = expand_variable(*line + i, env, &consumed);
			result = join_and_free(result, expanded);
			i += consumed;
			start = i;
			continue;
		}
		i++;
	}
	if (i > start)
	{
		temp = ft_strndup(*line + start, i - start);
		result = join_and_free(result, temp);
	}
	free(*line);
	*line = result;
}
