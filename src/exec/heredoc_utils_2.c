/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:58:27 by messengu          #+#    #+#             */
/*   Updated: 2025/09/13 13:00:25 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	close_all_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->pipefd[READ] > 2)
			close(tmp->pipefd[READ]);
		if (tmp->pipefd[WRITE] > 2)
			close(tmp->pipefd[WRITE]);
		tmp = tmp->next;
	}
}

void	handle_heredoc_interrupt(char *line, int *pipe_fd_h, t_cmd *cmd,
		t_env *env)
{
	if (line)
		free(line);
	close(pipe_fd_h[WRITE]);
	free_all_struct(cmd);
	free_my_env(env);
	exit(130);
}

int	process_heredoc_line(char *line, t_heredoc *heredoc, int *pipe_fd_h)
{
	if (line == NULL || g_signal == SIGINT)
		return (1);
	if (ft_strncmp(heredoc->delimiter, line, ft_strlen(line)) == 0
		&& ft_strlen(line) == ft_strlen(heredoc->delimiter))
		return (1);
	if (ft_strlen(line) > 1024)
		return (2);
	write(pipe_fd_h[WRITE], line, ft_strlen(line));
	write(pipe_fd_h[WRITE], "\n", 1);
	return (0);
}

void	handle_heredoc_parent(t_heredoc *heredoc, pid_t pid, int *pipe_fd_h)
{
	parent_ignore_signals();
	heredoc->heredoc_fd = parent_process_heredoc(pid, pipe_fd_h);
	handle_signals(0);
	if (heredoc->next && heredoc->heredoc_fd != -1)
	{
		close(heredoc->heredoc_fd);
		heredoc->heredoc_fd = -1;
	}
}
