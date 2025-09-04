/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:54 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/04 11:15:08 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	is_valid_number(char *str)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+'
			&& str[i] != 32)
			return (2);
		if (str[i] == '-' || str[i] == '+')
		{
			sign++;
			if (sign > 1)
				return (2);
		}
		i++;
	}
	return (0);
}

int	check_long(char *str)
{
	long long	nb;
	long long	min;

	nb = 0;
	min = -9223372036854775807LL;
	if (ft_strlen(str) > 20)
		return (1);
	nb = ft_atoll(str);
	if (nb >= 9223372036854775807 || nb <= min)
		return (1);
	return (0);
}

long long	ft_atoll(char *str)
{
	long long	i;
	long long	res;
	int			neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

static void	free_everything(t_cmd *cmd, t_env *env)
{
	free_all_struct(cmd);
	free_my_env(env);
}


int	built_in_exit(t_cmd *cmd, int exit_status, t_env *env)
{
	if (!(cmd->args && cmd->args[0]))
	{
		printf("exit\n");
		return (free_everything(cmd, env), exit(exit_status), 0);
	}
	if (cmd->args && invalid_option(cmd->args, "exit") == 2)
	{
		return (printf("minishell: exit: %c: There is no option allowed\n",
				cmd->args[0][0]), free_everything(cmd, env), exit(2), 2);
	}
	if (is_valid_number(cmd->args[0]) == 2)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[0]);
		return (free_everything(cmd, env), exit(2), 2);
	}
	if (check_long(cmd->args[0]) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[0]);
		return (free_everything(cmd, env), exit(2), 2);
	}
	if (cmd->args[1])
		return (printf("minishell: exit: too many arguments\n"), 2);
	return (printf("exit\n"), ft_atoll(cmd->args[0]) % 256);
}

// int	built_in_exit_bis(t_cmd *cmd, int exit_status)
// {
// 	if (!(cmd->args && cmd->args[0]))
// 	{
// 		return (free_all_struct(cmd), exit(exit_status), 0);
// 	}
// 	if (is_valid_number(cmd->args[0]) == 2)
// 	{
// 		printf("minishell: exit: %s: numeric argument required\n",
// 			cmd->args[0]);
// 		return (free_all_struct(cmd), exit(2), 2);
// 	}
// 	if (check_long(cmd->args[0]) == 1)
// 	{
// 		printf("minishell: exit: %s: numeric argument required\n",
// 			cmd->args[0]);
// 		return (free_all_struct(cmd), exit(2), 2);
// 	}
// 	if (cmd->args[1])
// 	{
// 		printf("minishell: exit: too many arguments\n");
// 		return (2);
// 	}
// 	return (ft_atoll(cmd->args[0]) % 256);
// }
