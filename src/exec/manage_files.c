/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/02 11:28:45 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	open_infile(t_cmd *cmd, int *pipe_fd)
{
	int		fd;
	t_file	*file;

	file = cmd->infile;
	if (cmd->output_type == PIPEOUT)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], FD_STDOUT);
		close(pipe_fd[WRITE]);
	}
	while (file && file->name)
	{
		fd = open(file->name, O_RDONLY);
		if (fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(fd, FD_STDIN);
		close(fd);
		file = file->next;
	}
}

void	open_outfile(t_cmd *cmd, int *pipe_fd)
{
	int		fd;
	t_file	*file;

	file = cmd->outfile;
	if (cmd->output_type == PIPEOUT)
	{
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
	}
	while (file && file->name)
	{
		if (file->append)
			fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			error(cmd, file->name, 1);
		}
		dup2(fd, FD_STDOUT);
		close(fd);
		file = file->next;
	}
}

void	child_process_heredoc(t_heredoc *heredoc, int *pipefd)
{
	char	*line;

	while (1)
	{
		line = readline("\033[36mheredoc> \033[0m");
		if (line == NULL)
			exit(0);
		if (ft_strncmp(heredoc->delimiter, line, ft_strlen(line)) == 0)
			break ;
		write(pipefd[WRITE], line, ft_strlen(line));
		write(pipefd[WRITE], "\n", 1);
		free(line);
	}
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	free(line);
	exit(0);
}

void	parent_process_heredoc(int *pipefd, pid_t pid)
{
	int	status;

	close(pipefd[WRITE]);
	waitpid(pid, &status, 0);
}

void	manage_heredocs(t_cmd *cmd)
{
	t_heredoc	*heredoc;
	int			pipefd[2];
	pid_t		pid;

	heredoc = cmd->heredocs;
	while (heredoc)
	{
		if (pipe(pipefd) == -1)
			error(cmd, "pipe failed\n", 1);
		pid = fork();
		if (pid == -1)
			error(cmd, "fork failed\n", 1); // besoin de proteger les fermetures de pipe a chaque erreur
		if (pid == 0)
			child_process_heredoc(heredoc, pipefd);
		else
		{
			parent_process_heredoc(pipefd, pid);
			if (heredoc->heredoc_fd != -1)
				close(heredoc->heredoc_fd);
			heredoc->heredoc_fd = pipefd[READ]; // quand fermer ce fd correctement ?
		}
		heredoc = heredoc->next;
		// if (heredoc->next)
		// 	close(heredoc->heredoc_fd);
		// close(pipefd[READ]); // boucle infini
	}
}
