/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:54 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/12 12:40:55 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

static void	free_everything(t_cmd *cmd, t_env *env, char *str)
{
	if (str)
		printf("%s\n", str);
	free_all_struct(cmd);
	free_my_env(env);
}

int	invalid_option_exit(char **args)
{
	int	i;

	if (args)
	{
		if (args[0][0] == '-' && !args[0][1])
			return (2);
		if (args[0][0] == '-' && args[0][1])
		{
			i = 1;
			while (args[0][i])
			{
				if (!ft_isdigit(args[0][i]))
					return (2);
				i++;
			}
		}
	}
	return (0);
}

int	built_in_exit(t_cmd *cmd, t_env *env)
{
	int	last_exit_status;

	last_exit_status = env->exit_status;
	if (!(cmd->args && cmd->args[0]))
		return (free_everything(cmd, env, "exit"), exit(last_exit_status), 0);
	if (cmd->args && invalid_option_exit(cmd->args) == 2)
		return (printf("minishell: exit: %c: There is no option allowed\n",
				cmd->args[0][0]), free_everything(cmd, env, NULL), exit(2), 2);
	if (is_valid_number(cmd->args[0]) == 2)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[0]);
		return (free_everything(cmd, env, NULL), exit(2), 2);
	}
	if (check_long(cmd->args[0]) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[0]);
		return (free_everything(cmd, env, NULL), exit(2), 2);
	}
	if (cmd->args[1])
		return (printf("minishell: exit: too many arguments\n"), 2);
	last_exit_status = ft_atoll(cmd->args[0]) % 256;
	return (free_everything(cmd, env, "exit"), exit(last_exit_status), 0);
}
