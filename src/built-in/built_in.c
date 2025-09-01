/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:48:50 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/15 15:59:30 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

bool	is_built_in(t_cmd *cmd)
{
	if (cmd == NULL || cmd->name == NULL)
		return (false);
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		return (true);
	if (ft_strncmp(cmd->name, "cd", 2) == 0)
		return (true);
	if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd->name, "export", 6) == 0)
		return (true);
	if (ft_strncmp(cmd->name, "unset", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->name, "env", 3) == 0)
		return (true);
	if (ft_strncmp(cmd->name, "exit", 4) == 0)
		return (true);
	return (false);
}

int	parent_process_built_in(t_cmd *cmd, t_env *env)
{
    int code_error;

    code_error = 0;
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		code_error = built_in_echo(cmd);
	if (ft_strncmp(cmd->name, "cd", 2) == 0)
		code_error = built_in_cd(cmd, env);
	if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		code_error = built_in_pwd(cmd);
	if (ft_strncmp(cmd->name, "export", 6) == 0)
		code_error = built_in_export(cmd, env, code_error);
	if (ft_strncmp(cmd->name, "unset", 5) == 0)
		code_error =  built_in_unset(cmd, env);
	if (ft_strncmp(cmd->name, "env", 3) == 0)
		code_error = built_in_env(cmd, env);
	if (ft_strncmp(cmd->name, "exit", 4) == 0)
	    code_error = built_in_exit(cmd, code_error);
    return (code_error);
}

int	child_process_built_in(t_cmd *cmd, t_env *env)
{
    int code_error;

    code_error = 0;
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		code_error = built_in_echo(cmd);
	if (ft_strncmp(cmd->name, "cd", 2) == 0)
		code_error = built_in_cd(cmd, env);
	if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		code_error = built_in_pwd(cmd);
	if (ft_strncmp(cmd->name, "export", 6) == 0)
		code_error = built_in_export(cmd, env, code_error);
	if (ft_strncmp(cmd->name, "unset", 5) == 0)
		code_error =  built_in_unset(cmd, env);
	if (ft_strncmp(cmd->name, "env", 3) == 0)
		code_error = built_in_env(cmd, env);
    return (code_error);
}
