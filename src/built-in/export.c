/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:58 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/09 15:14:35 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	check_head_var(char *var)
{
	int	i;

	i = 0;
	if ((var[0] != '_' && ft_isalpha(var[0]) == 0) || var[0] == '=')
		return (-1);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (-1);
		i++;
	}
	if (var[i] == '=' && var[i + 1])
		return (i);
	if (var[i] == '=' && !var[i + 1])
		return (0);
	return (-2);
}

int	check_export_format(char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = check_head_var(var);
	if (i == -1)
		return (1);
	if (i == -2)
		return (-404);
	i++;
	if (var[i] == ' ')
		return (0);
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_' && var[i] != '/'
			&& var[i] != '-' && var[i] == '=' && len > 100)
			return (1);
		i++;
	}
	return (0);
}

int	built_in_export(t_cmd *cmd, t_env *env, int code_error)
{
	int	i;

	i = 0;
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args && invalid_option(cmd->args, "export"))
		return (printf("minishell: export: '-': There is no option allowed\n"),
			2);
	while (cmd->args && cmd->args[i])
	{
		code_error = check_export_format(cmd->args[i]);
		if (code_error == 1)
		{
			printf("minishell: export: %s: not a valid identifier\n",
				cmd->args[i]);
		}
		if (code_error == 0)
			if (cmd->args && cmd->args[i] && get_my_export_env(&(env->env),
					cmd->args[i]) == 1)
				return (1);
		i++;
	}
	return (code_error);
}
