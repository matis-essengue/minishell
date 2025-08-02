/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:39:21 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/01 18:39:49 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	child_call(t_cmd *cmd, int *pipefd, char **envp)
{
	if (cmd->heredocs)
	{
		dup2(cmd->heredocs->heredoc_fd, FD_STDIN);
		close(cmd->heredocs->heredoc_fd);
	}
	else if (cmd->infile && cmd->infile->name)
		open_infile(cmd, pipefd);
	
	if (cmd->outfile && cmd->outfile->name)
		open_outfile(cmd, pipefd);
	else if (cmd->output_type == PIPEOUT)
	{
		// Fermer le côté lecture qu'on n'utilise pas
		close(pipefd[READ]);
		dup2(pipefd[WRITE], FD_STDOUT);
		close(pipefd[WRITE]);
	}
	
	exe_my_cmd(cmd, envp);
}

void	parent_call(t_cmd *cmd, int *pipefd)
{
	// Le parent ferme le côté écriture du pipe
	if (cmd->output_type == PIPEOUT)
	{
		close(pipefd[WRITE]);
		// Ne pas rediriger stdin ici - le faire dans la prochaine itération
	}
}

void	setup_pipe_input(int *prev_pipe_read)
{
	if (*prev_pipe_read != -1)
	{
		dup2(*prev_pipe_read, FD_STDIN);
		close(*prev_pipe_read);
		*prev_pipe_read = -1;
	}
}

void	wait_child(void)
{
	while (wait(NULL) > 0)
		;
}

void	restore_old_fd(int *old_fd)
{
	if ((dup2(old_fd[READ], READ) == -1) || dup2(old_fd[WRITE], WRITE) == -1)
	{
		perror("dup error\n");
	}
	// IMPORTANT: Fermer les old_fd après restauration
	close(old_fd[READ]);
	close(old_fd[WRITE]);
}

void	pipe_function(t_cmd *cmd, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		old_fd[2];
	int		prev_pipe_read = -1;
	
	// Sauvegarder les fd originaux
	if (((old_fd[0] = dup(READ)) == -1) || ((old_fd[1] = dup(WRITE)) == -1))
		return (error(cmd, "dup error\n", 1));
	
	while (cmd)
	{
		// Gérer l'input du pipe précédent
		setup_pipe_input(&prev_pipe_read);
		
		if (cmd->heredocs)
			manage_heredocs(cmd);
			
		// Créer un pipe seulement si nécessaire
		if (cmd->output_type == PIPEOUT)
		{
			if (pipe(pipefd) == -1)
				error(cmd, "pipe failed", 1);
		}
		
		pid = fork();
		if (pid == -1)
			error(cmd, "fork failed", 1);
			
		if (pid == 0)
			child_call(cmd, pipefd, envp);
		else
		{
			// Dans le parent
			if (cmd->output_type == PIPEOUT)
			{
				close(pipefd[WRITE]);
				prev_pipe_read = pipefd[READ]; // Sauvegarder pour la prochaine commande
			}
		}
		
		cmd = cmd->next;
	}
	
	// Fermer le dernier pipe_read s'il existe
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
		
	wait_child();
	restore_old_fd(old_fd);
}

/* ************************************************************************** */
/*   manage_files.c (PARTIE CORRIGÉE)                                        */
/* ************************************************************************** */

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
		{
			close(pipefd[READ]);
			close(pipefd[WRITE]);
			error(cmd, "fork failed\n", 1);
		}
		if (pid == 0)
			child_process_heredoc(heredoc, pipefd);
		else
		{
			close(pipefd[WRITE]); // Parent ferme le côté écriture
			parent_process_heredoc(pid);
			
			// IMPORTANT: Fermer l'ancien heredoc_fd s'il existe
			if (heredoc->heredoc_fd != -1)
				close(heredoc->heredoc_fd);
				
			heredoc->heredoc_fd = pipefd[READ];
		}
		heredoc = heredoc->next;
	}
}

/* ************************************************************************** */
/*   errors.c (PARTIE CORRIGÉE)                                             */
/* ************************************************************************** */

void	free_files(t_cmd *cmd)
{
	t_file *tmp;
	t_heredoc *tmp_h;
	
	while (cmd->infile)
	{
		free(cmd->infile->name);
		tmp = cmd->infile->next;
		free(cmd->infile);
		cmd->infile = tmp;
	}
	while (cmd->outfile)
	{
		free(cmd->outfile->name);
		tmp = cmd->outfile->next;
		free(cmd->outfile);
		cmd->outfile = tmp;
	}
	while (cmd->heredocs)
	{
		free(cmd->heredocs->delimiter);
		free(cmd->heredocs->content);
		// IMPORTANT: Fermer le fd du heredoc
		if (cmd->heredocs->heredoc_fd != -1)
			close(cmd->heredocs->heredoc_fd);
		tmp_h = cmd->heredocs->next;
		free(cmd->heredocs);
		cmd->heredocs = tmp_h;
	}
}