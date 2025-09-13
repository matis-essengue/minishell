/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:48:50 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/12 12:41:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	redir_and_restore_stdout(t_cmd *cmd)
{
	int		prev_old_fd;
	t_file	*file;

	prev_old_fd = dup(FD_STDOUT);
	file = cmd->outfile;
	while (file && file->name)
	{
		if (file->append)
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->fd == -1)
		{
			perror(file->name);
			dup2(prev_old_fd, FD_STDOUT);
			close(prev_old_fd);
			return (-1);
		}
		dup2(file->fd, FD_STDOUT);
		close(file->fd);
		file = file->next;
	}
	return (prev_old_fd);
}

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

static int	execute_builtin_command(t_cmd *cmd, t_env *env, int code_error)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (built_in_echo(cmd));
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (built_in_cd(cmd, env));
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (built_in_pwd(cmd));
	if (ft_strcmp(cmd->name, "export") == 0)
		return (built_in_export(cmd, env, code_error));
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (built_in_unset(cmd, env));
	if (ft_strcmp(cmd->name, "env") == 0)
		return (built_in_env(cmd, env));
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (built_in_exit(cmd, env));
	return (code_error);
}

int	parent_process_built_in(t_cmd *cmd, t_env *env)
{
	int	code_error;
	int	prev_old_fd;

	code_error = 0;
	prev_old_fd = -1;
	if (cmd->outfile && cmd->outfile->name)
	{
		prev_old_fd = redir_and_restore_stdout(cmd);
		if (prev_old_fd == -1)
			return (1);
	}
	code_error = execute_builtin_command(cmd, env, code_error);
	if (prev_old_fd > 0)
		return (dup2(prev_old_fd, FD_STDOUT), close(prev_old_fd), code_error);
	return (code_error);
}

int	child_process_built_in(t_cmd *cmd, t_env *env)
{
	int	code_error;

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
		code_error = built_in_unset(cmd, env);
	if (ft_strcmp(cmd->name, "env") == 0)
		code_error = built_in_env(cmd, env);
	return (code_error);
}
