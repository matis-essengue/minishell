/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:27:20 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/09 11:38:36 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

char	**copy_and_replace_my_env(char **env, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (env_len(env) + 1));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (check_is_same_var(env[i], var))
			tmp[i] = ft_strdup(var);
		else
			tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
		{
			free_array(tmp);
			return (NULL);
		}
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**copy_and_add_my_env(char **env, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (env_len(env) + 2));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
		{
			free_array(tmp);
			return (NULL);
		}
		i++;
	}
	tmp[i] = ft_strdup(var);
	if (!tmp[i])
	{
		free_array(tmp);
		return (NULL);
	}
	tmp[++i] = NULL;
	return (tmp);
}

int	get_my_export_env(char ***env, char *new_var)
{
	char	**tmp;
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (check_is_same_var((*env)[i], new_var))
		{
			tmp = copy_and_replace_my_env(*env, new_var);
			if (!tmp)
				return (1);
			free_array(*env);
			*env = tmp;
			return (0);
		}
		i++;
	}
	tmp = copy_and_add_my_env(*env, new_var);
	if (!tmp)
		return (1);
	free_array(*env);
	*env = tmp;
	return (0);
}

char	*ft_getenv(char *var, char **env)
{
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(var);
	if (!var || !env || !env[i] || len == 0)
		return (NULL);
	while (env[i])
	{
		if (check_is_same_var(var, env[i]))
		{
			while (env[i][j] && env[i][j] != '=')
				j++;
			if (env[i][j] == '=')
			{
				j++;
				return (ft_strdup(env[i] + j));
			}
		}
		i++;
	}
	return (NULL);
}
