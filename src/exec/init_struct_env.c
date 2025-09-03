/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:17:52 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/03 16:59:29 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// PWD=/home/armosnie/42/3_circle/armandbranch
// SHLVL=1
// _=/usr/bin/env

char	*get_pwd(void)
{
	char	*pwd;
	char	buffer[1024];

	pwd = getcwd(buffer, 1024);
	if (!pwd)
	{
		perror("");
		return (NULL);
	}
	return (pwd);
}

char	**build_mini_env()
{
	char	**mini_env;
	int		i;

	i = 0;
	
	mini_env = malloc(sizeof(char *) * (4));
	if (!mini_env)
		return (NULL);
	mini_env[i] = get_pwd();
	if (!mini_env[i])
		return (perror(""), NULL);
	i++;
	mini_env[i] = ft_strdup("SHLVL=1");
	if (!mini_env)
		return (NULL);
	mini_env[++i] = ft_strdup("_=/usr/bin/env");
	if (!mini_env)
		return (free_array(mini_env), NULL);
	mini_env[++i] = NULL;
	return (mini_env);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!envp)
	{
		new_env = build_mini_env();
		return (new_env);
	}
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
