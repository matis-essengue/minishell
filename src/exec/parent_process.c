/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/13 11:35:00 by messengu         ###   ########.fr       */
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

int	manage_parent_call(t_cmd *cmd)
{
	t_heredoc	*heredoc;
	int			prev_read_fd;

	prev_read_fd = -1;
	prev_read_fd = parent_call(cmd, prev_read_fd);
	if (cmd->heredocs)
	{
		heredoc = cmd->heredocs;
		while (heredoc)
		{
			if (heredoc->heredoc_fd != -1)
			{
				close(heredoc->heredoc_fd);
				heredoc->heredoc_fd = -1;
			}
			heredoc = heredoc->next;
		}
	}
	return (prev_read_fd);
}

void	end_pipe_function(t_cmd *first_cmd, t_cmd *cmd, int prev_read_fd)
{
	if (prev_read_fd != -1)
		close(prev_read_fd);
	cmd = first_cmd;
	while (cmd)
	{
		if (cmd->pipefd[READ] > 2)
			close(cmd->pipefd[READ]);
		if (cmd->pipefd[WRITE] > 2)
			close(cmd->pipefd[WRITE]);
		cmd = cmd->next;
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
		if (single_heredoc(cmd, cmd_list, env, prev_read_fd) != 1)
		{
			if (cmd->heredocs)
				manage_heredocs(cmd, cmd_list, prev_read_fd, env);
			pipe_check_or_create(cmd, pid, i, prev_read_fd);
			if (pid[i] == 0)
				child_call(cmd, cmd_list, env, prev_read_fd);
			else
				prev_read_fd = manage_parent_call(cmd);
			i++;
		}
		cmd = cmd->next;
	}
	end_pipe_function(cmd_list, cmd, prev_read_fd);
	return (exit_status = wait_child(pid, i));
}

int	execute_command(t_cmd *cmd, t_env *env)
{
	pid_t			pid[MAX_PROCESSES];
	int				exit_status;
	struct termios	saved_term;
	int				had_saved;

	if (save_termios(&saved_term) == 0)
		had_saved = 1;
	if (!cmd)
	{
		if (had_saved)
			restore_termios(&saved_term);
		return (1);
	}
	handle_signals(0);
	exit_status = 0;
	if (cmd->output_type != PIPEOUT && !cmd->next && is_built_in(cmd))
		exit_status = parent_process_built_in(cmd, env);
	else
		exit_status = pipe_function(cmd, pid, exit_status, env);
	handle_signals(1);
	if (had_saved)
		restore_termios(&saved_term);
	return (exit_status);
}
