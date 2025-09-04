/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:49 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/04 15:47:52 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	built_in_env(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!env->env || !env->env[i])
		return (1);
	if (cmd->args && invalid_option(cmd->args, "env") == 2)
	{
		printf("env: There is no option\n");
		return (1);
	}
	if (cmd->args && (cmd->args[0] || cmd->args[1]))
	{
		printf("env: Too many arguments\n");
		return (1);
	}
	while (env->env && env->env[i])
	{
		printf("%s\n", env->env[i]);
		i++;
	}
	return (0);
}
