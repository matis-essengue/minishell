/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:05:29 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/30 16:38:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// void	is_built_in(t_cmd *cmd)
// {
// }

// cmd->heredocs->expand_vars == false && 

void	child_call(t_cmd *cmd, int *pipefd, char **envp)
{
	if (cmd->infile != NULL)
		manage_infile(cmd, pipefd);
	else if (cmd->outfile != NULL)
		manage_outfile(cmd, pipefd);
	// else if (cmd->input_type == HERE_DOC)
	// 	manage_here_doc(cmd);
	else if (cmd->next)
	{
		close(pipefd[READ]);
		dup2(pipefd[WRITE], STDOUT_FILENO);
		close(pipefd[WRITE]);
	}
    exe_my_cmd(cmd, envp);
}

void	parent_call(int *pipefd)
{
	close(pipefd[WRITE]);
	dup2(pipefd[READ], FD_STDIN);
	close(pipefd[READ]);
}

void	wait_child(void)
{
	while (wait(NULL) > 0)
		;
}

void	pipe_function(t_cmd *cmd, char **envp)
{
	pid_t pid;
	int pipefd[2];
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (cmd != NULL)
	{
		if (cmd->input_type == PIPEIN || count_cmd(cmd) > 1)
			pipe(pipefd);
		pid = fork();
		if (pid == -1)
			error("fork failed\n", 1);
		if (pid == 0)
			child_call(cmd, pipefd, envp);
		else
			parent_call(pipefd);
		cmd = cmd->next;
	}
	wait_child();
	restore_all_in_out(saved_stdin, saved_stdout);
}
