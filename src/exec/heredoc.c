/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:36:33 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/13 13:00:20 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

static void	read_heredoc_input(t_heredoc *heredoc, int *pipe_fd_h, t_cmd *cmd,
		t_env *env)
{
	char	*line;
	int		status;

	while (1)
	{
		line = readline("\033[36mheredoc> \033[0m");
		if (g_signal == SIGINT)
			handle_heredoc_interrupt(line, pipe_fd_h, cmd, env);
		status = process_heredoc_line(line, heredoc, pipe_fd_h);
		if (status == 2)
		{
			free_all_struct(cmd);
			free_my_env(env);
			close(pipe_fd_h[WRITE]);
			free(line);
			exit(0);
		}
		if (status == 1)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

int	child_process_heredoc(t_cmd *cmd, t_heredoc *heredoc, int *pipe_fd_h,
		t_env *env)
{
	close(pipe_fd_h[READ]);
	close_all_pipes(cmd);
	g_signal = 0;
	handle_heredoc_signals();
	read_heredoc_input(heredoc, pipe_fd_h, cmd, env);
	close(pipe_fd_h[WRITE]);
	free_all_struct(cmd);
	free_my_env(env);
	exit(0);
}

int	parent_process_heredoc(pid_t pid, int *pipe_fd_h)
{
	int	status;

	close(pipe_fd_h[WRITE]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || (WIFEXITED(status)
			&& WEXITSTATUS(status) == 130))
	{
		close(pipe_fd_h[READ]);
		return (-1);
	}
	return (pipe_fd_h[READ]);
}

static void	handle_heredoc_child(t_cmd *cmd, t_heredoc *heredoc, int *pipe_fd_h,
		t_env *env)
{
	handle_heredoc_signals();
	child_process_heredoc(cmd, heredoc, pipe_fd_h, env);
}

int	manage_heredocs(t_cmd *current, t_cmd *cmd, int prev_read_fd, t_env *env)
{
	t_heredoc	*heredoc;
	pid_t		pid;
	int			pipe_fd_h[2];

	heredoc = current->heredocs;
	if (check_heredoc_total(cmd) == 2)
		return (2);
	while (heredoc)
	{
		if (pipe(pipe_fd_h) == -1)
			pipe_and_pid_error(cmd, heredoc, pipe_fd_h, 1);
		pid = fork();
		if (pid == -1)
			pipe_and_pid_error(cmd, heredoc, pipe_fd_h, 2);
		if (pid == 0)
		{
			if (prev_read_fd > 2)
				close(prev_read_fd);
			handle_heredoc_child(cmd, heredoc, pipe_fd_h, env);
		}
		else
			handle_heredoc_parent(heredoc, pid, pipe_fd_h);
		heredoc = heredoc->next;
	}
	return (0);
}
