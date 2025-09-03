/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:17:52 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/01 16:35:41 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// PWD=/home/armosnie/42/3_circle/armandbranch
// SHLVL=1
// _=/usr/bin/env

// char	**build_mini_env(char **envp)
// {
// 	char *pwd;

// 	pwd = getcwd(buffer, 1024);
//     if (!pwd)
//     {
//         perror("");
//         return (1);
//     }
// }

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	// if (!envp)
	// 	return (build_mini_env(envp));
	new_env = malloc(sizeof(char *) * (env_len(envp) + 1));
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (new_env[i] == NULL)
		{
			while (i > -1)
			{
				free(new_env[i]);
				i--;
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_env	*init_env(char **envp)
{
	t_env	*my_env;

	my_env = malloc(sizeof(t_env));
	if (!my_env)
		return (NULL);
	my_env->env = copy_env(envp);
	if (!my_env->env)
	{
		free(my_env);
		return (NULL);
	}
	my_env->is_cpy = 1;
	return (my_env);
}

void	free_my_env(t_env *my_env)
{
	if (!my_env)
		return ;
	if (my_env->is_cpy == 1 && my_env->env)
	{
		free_array(my_env->env);
	}
	if (my_env)
		free(my_env);
}