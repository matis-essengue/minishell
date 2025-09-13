/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:20:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/13 12:21:30 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

char	**unset_replace_my_env(char **env, char *var)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * env_len(env));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (!check_is_same_var(env[i], var))
		{
			tmp[j] = ft_strdup(env[i]);
			if (!tmp[j])
			{
				free_array(tmp);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

int	get_my_unset_env(char ***env, char *new_var)
{
	char	**tmp;
	char	*var_path;
	int		i;

	i = 0;
	var_path = get_var_path(*(env), new_var);
	if (var_path == NULL)
		return (0);
	while ((*env)[i])
	{
		if (check_is_same_var((*env)[i], var_path))
		{
			tmp = unset_replace_my_env(*env, var_path);
			if (!tmp)
				return (free(var_path), 1);
			free_array(*env);
			*env = tmp;
			free(var_path);
			return (0);
		}
		i++;
	}
	free(var_path);
	return (0);
}

int	built_in_unset(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args && invalid_option(cmd->args, "unset"))
		return (printf("minishell: unset: '-': There is no option allowed\n"),
			2);
	while (cmd->args[i])
	{
		if (get_my_unset_env(&env->env, cmd->args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
