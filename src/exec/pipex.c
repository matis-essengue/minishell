/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:05:29 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/04 16:12:40 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	child_call(t_data *data, int *pipefd, int i)
{
	if (i == 0 && data->here_doc == false)
		manage_infile(data, pipefd);
	else if (i == data->n_cmd - 1)
		manage_outfile(data, pipefd);
	else
	{
		close(pipefd[READ]);
		dup2(pipefd[WRITE], STDOUT);
		close(pipefd[WRITE]);
	}
    exe_my_cmd(data->cmd[i], data->envp);
}

void	parent_call(int *pipefd)
{
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN);
	close(pipefd[READ]);
}

void	wait_child(void)
{
	while (wait(NULL) > 0)
		;
}

void	pipe_function(t_data *data)
{
	pid_t pid;
	int pipefd[2];
	int i;

	i = 0;
	while (data->cmd[i] != NULL)
	{
		if (!(i == data->n_cmd - 1) && pipe(pipefd) == -1)
			error("pipe failed\n", 1);
        pid = fork();
		if (pid == -1)
			error("fork failed\n", 1);
		if (pid == 0)
			child_call(data, pipefd, i);
		else
			parent_call(pipefd);
		i++;
	}
	close(STDIN);
	wait_child();
}