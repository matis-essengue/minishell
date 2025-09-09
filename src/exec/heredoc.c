/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:46:02 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/09 16:22:40 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	heredoc_signal(char *line, int *pipe_fd_h)
{
	if (g_signal == SIGINT)
	{
		free(line);
		close(pipe_fd_h[WRITE]);
		exit(1);
	}
}

int	child_process_heredoc(t_cmd *cmd, t_heredoc *heredoc, int *pipe_fd_h)
{
	char	*line;

	(void)cmd;
	close(pipe_fd_h[READ]);
	heredoc_signal_handler();
	while (1)
	{
		line = readline("\033[36mheredoc> \033[0m");
		if (line == NULL)
			break ;
		heredoc_signal(line, pipe_fd_h);
		if (ft_strncmp(heredoc->delimiter, line, ft_strlen(line)) == 0
			&& ft_strlen(line) == ft_strlen(heredoc->delimiter))
			break ;
		if (ft_strlen(line) > 1024)
			return (close(pipe_fd_h[WRITE]), free(line), exit(0), 0);
		write(pipe_fd_h[WRITE], line, ft_strlen(line));
		write(pipe_fd_h[WRITE], "\n", 1);
		free(line);
	}
	close(pipe_fd_h[WRITE]);
	return (free(line), exit(0), 0);
}

int	parent_process_heredoc(pid_t pid, int *pipe_fd_h)
{
	int	status;

	close(pipe_fd_h[WRITE]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	interactive_signal_handler();
	if (WIFSIGNALED(status))
	{
		close(pipe_fd_h[READ]);
		return (-1);
	}
	return (pipe_fd_h[READ]);
}

void	manage_heredocs(t_cmd *cmd)
{
	t_heredoc	*heredoc;
	pid_t		pid;
	int			pipe_fd_h[2];

	heredoc = cmd->heredocs;
	while (heredoc)
	{
		if (pipe(pipe_fd_h) == -1)
			pipe_and_pid_error(cmd, heredoc, pipe_fd_h, 1);
		pid = fork();
		if (pid == -1)
			pipe_and_pid_error(cmd, heredoc, pipe_fd_h, 2);
		if (pid == 0)
			child_process_heredoc(cmd, heredoc, pipe_fd_h);
		else
			heredoc->heredoc_fd = parent_process_heredoc(pid, pipe_fd_h);
		if (heredoc->next && heredoc->heredoc_fd != -1)
		{
			close(heredoc->heredoc_fd);
			heredoc->heredoc_fd = -1;
		}
		heredoc = heredoc->next;
	}
}
