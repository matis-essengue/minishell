/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:13:31 by matis             #+#    #+#             */
/*   Updated: 2025/09/08 15:12:42 by matis            ###   ########.fr       */
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

char	*_get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_strndup(str, i);
	return (var_name);
}

char	*handle_special_vars(char *str, t_env *env, int *consumed)
{
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
	return (NULL);
}

char	*expand_variable(char *str, t_env *env, int *consumed, int is_escaped)
{
	char	*var_name;
	char	*value;
	char	*special_result;

	special_result = handle_special_vars(str, env, consumed);
	if (special_result)
		return (special_result);
	var_name = _get_var_name(str + 1);
	if (is_escaped)
	{
		*consumed = ft_strlen(var_name) + 2;
		value = ft_strjoin("$", var_name);
		free(var_name);
		return (value);
	}
	*consumed = ft_strlen(var_name) + 1;
	value = ft_getenvx(var_name, env->env);
	free(var_name);
	if (value)
		return (value);
	return (ft_strdup(""));
}
