/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:05:29 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/13 18:52:45 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	child_call(t_cmd *cmd, int *pipefd, char **envp)
{
	if (cmd->heredocs->expand_vars == false)
		manage_infile(cmd, pipefd);
	else if (cmd->next->next == NULL)
		manage_outfile(cmd, pipefd);
	else
	{
		close(pipefd[READ]);
		dup2(pipefd[WRITE], FD_STDOUT);
		close(pipefd[WRITE]);
	}
    exe_my_cmd(cmd, envp);
}

void	parent_call(int *pipefd)
{
	close(pipefd[FD_STDIN]);
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
	int i;

	i = 0;
	while (cmd != NULL)
	{
		if (cmd->input_type == PIPEIN)
			pipe(pipefd);
		pid = fork();
		if (pid == -1)
			error("fork failed\n", 1);
		if (pid == 0)
			child_call(cmd, pipefd, cmd);
		else
			parent_call(pipefd);
		cmd = cmd->next;
	}
	close(STDIN);
	wait_child();
}