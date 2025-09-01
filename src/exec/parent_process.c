/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/17 14:11:33 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	parent_call(t_cmd *cmd, int prev_read_fd)
{
	if (prev_read_fd != -1)
		close(prev_read_fd);
	if (cmd->output_type == PIPEOUT)
	{
		close(cmd->pipefd[WRITE]);
		prev_read_fd = cmd->pipefd[READ];
	}
	else
		prev_read_fd = -1;
	return (prev_read_fd);
}

void	pipe_check_or_create(t_cmd *cmd, int prev_read_fd)
{
	if (cmd->output_type == PIPEOUT && pipe(cmd->pipefd) == -1)
	{
		if (prev_read_fd != -1)
			close(prev_read_fd);
		error(cmd, "pipe failed", 1);
	}
}

void	pidarray_check(t_cmd *cmd, pid_t *pid, int prev_read_fd, int i)
{
	if (pid[i] == -1)
	{
		if (prev_read_fd != -1)
			close(prev_read_fd);
		if (cmd->output_type == PIPEOUT)
		{
			close_all_fd(cmd->pipefd);
			error(cmd, "fork failed", 1);
		}
	}
}

int	pipe_function(t_cmd *cmd, pid_t *pid, int exit_status, t_env *env)
{
	t_cmd	*cmd_list;
	int		prev_read_fd;
	int		i;

	i = 0;
	prev_read_fd = -1;
	cmd_list = cmd;
	while (cmd && i < MAX_PROCESSES)
	{
		if (cmd->heredocs)
			manage_heredocs(cmd, env);
		pipe_check_or_create(cmd, prev_read_fd);
		pid[i] = fork();
		pidarray_check(cmd, pid, prev_read_fd, i);
		if (pid[i] == 0)
			child_call(cmd, cmd_list, env, prev_read_fd);
		else
			prev_read_fd = parent_call(cmd, prev_read_fd);
		i++;
		cmd = cmd->next;
	}
	if (prev_read_fd != -1)
		close(prev_read_fd);
	exit_status = wait_child(pid, i);
	return (exit_status);
}

int	execute_command(t_cmd *cmd, t_env *env)
{
	pid_t pid[MAX_PROCESSES];
	int exit_status;

	if (!cmd)
		return (1);
	exit_status = 0;
	if (cmd->output_type != PIPEOUT && !cmd->next && is_built_in(cmd))
		exit_status = parent_process_built_in(cmd, env);
	else
		exit_status = pipe_function(cmd, pid, exit_status, env);
	free_all_struct(cmd);
	return (exit_status);
}
