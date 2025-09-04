/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:48:50 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/04 14:05:16 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

bool	is_built_in(t_cmd *cmd)
{
	if (cmd == NULL || cmd->name == NULL)
		return (false);
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (true);
	return (false);
}

int	parent_process_built_in(t_cmd *cmd, t_env *env)
{
    int code_error;

    code_error = 0;
	if (cmd->outfile && cmd->outfile->name)
	{
		open_outfile(cmd);
	}
	if (ft_strcmp(cmd->name, "echo") == 0)
		code_error = built_in_echo(cmd);
	if (ft_strcmp(cmd->name, "cd") == 0)
		code_error = built_in_cd(cmd, env);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		code_error = built_in_pwd(cmd);
	if (ft_strcmp(cmd->name, "export") == 0)
		code_error = built_in_export(cmd, env, code_error);
	if (ft_strcmp(cmd->name, "unset") == 0)
		code_error =  built_in_unset(cmd, env);
	if (ft_strcmp(cmd->name, "env") == 0)
		code_error = built_in_env(cmd, env);
	if (ft_strcmp(cmd->name, "exit") == 0)
	    code_error = built_in_exit(cmd, code_error, env);
    return (code_error);
}

int	child_process_built_in(t_cmd *cmd, t_env *env)
{
    int code_error;

    code_error = 0;
	if (ft_strcmp(cmd->name, "echo") == 0)
		code_error = built_in_echo(cmd);
	if (ft_strcmp(cmd->name, "cd") == 0)
		code_error = built_in_cd(cmd, env);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		code_error = built_in_pwd(cmd);
	if (ft_strcmp(cmd->name, "export") == 0)
		code_error = built_in_export(cmd, env, code_error);
	if (ft_strcmp(cmd->name, "unset") == 0)
		code_error =  built_in_unset(cmd, env);
	if (ft_strcmp(cmd->name, "env") == 0)
		code_error = built_in_env(cmd, env);
    return (code_error);
}
