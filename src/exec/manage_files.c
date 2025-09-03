/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/03 16:48:43 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	open_infile(t_cmd *cmd)
{
	t_file	*file;

	file = cmd->infile;
	while (file && file->name)
	{
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(file->fd, FD_STDIN);
		close(file->fd);
		file = file->next;
	}
}

void	open_outfile(t_cmd *cmd)
{
	t_file	*file;

	file = cmd->outfile;
	while (file && file->name)
	{
		if (file->append)
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (file->fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(file->fd, FD_STDOUT);
		close(file->fd);
		file = file->next;
	}
}

int	child_process_heredoc(t_cmd *cmd, t_heredoc *heredoc, int *pipe_fd_h)
{
	char	*line;
	char 	*expand;

	expand = NULL;
	close(pipe_fd_h[READ]);
	while (1)
	{
		line = readline("\033[36mheredoc> \033[0m");
		if (line == NULL)
			exit(1);
		if (ft_strncmp(heredoc->delimiter, line, ft_strlen(line)) == 0)
			break ;
		write(pipe_fd_h[WRITE], line, ft_strlen(line));
		write(pipe_fd_h[WRITE], "\n", 1);
		free(line);
	}
	close(pipe_fd_h[WRITE]);
	return (free(line), free_all_struct(cmd), exit(0), 0);
}

int	parent_process_heredoc(pid_t pid, int *pipe_fd_h)
{
	close(pipe_fd_h[WRITE]);
	waitpid(pid, NULL, 0);
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
