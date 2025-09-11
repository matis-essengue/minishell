/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:17:52 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/04 15:37:46 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	*result;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("");
		return (NULL);
	}
	result = ft_strjoin("PWD=", pwd);
	free(pwd);
	return (result);
}

char	**build_mini_env(void)
{
	char	**mini_env;

	printf("build_mini_env\n");
	mini_env = malloc(sizeof(char *) * (4));
	if (!mini_env)
		return (NULL);
	mini_env[0] = get_pwd();
	if (!mini_env[0])
		return (free(mini_env), NULL);
	mini_env[1] = ft_strdup("SHLVL=1");
	if (!mini_env[1])
		return (free_array(mini_env), NULL);
	mini_env[2] = ft_strdup("_=/usr/bin/env");
	if (!mini_env[2])
		return (free_array(mini_env), NULL);
	mini_env[3] = NULL;
	return (mini_env);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!envp || !envp[0])
		return (build_mini_env());
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
			return (free(new_env), NULL);
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
	my_env->exit_status = 0;
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
