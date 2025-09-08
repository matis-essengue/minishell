/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:32:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/08 17:07:48 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	command_not_found_error(t_cmd *cmd, char *command_name)
{
	printf("minishell: %s: command not found\n", command_name);
	free_all_struct(cmd);
	exit(127);
}

void	free_array(char **split)
{
	int	j;

	j = 0;
	if (!split)
		return ;
	while (split[j])
	{
		free(split[j]);
		split[j] = NULL;
		j++;
	}
	free(split);
}

void	close_all_fd(int *fd)
{
	if (fd[READ] != -1)
		close(fd[READ]);
	if (fd[WRITE] != -1)
		close(fd[WRITE]);
}

void	pipe_and_pid_error(t_cmd *cmd, t_heredoc *heredoc, int *pipe_fd_h,
		int err)
{
	if (err == 1)
	{
		if (heredoc->heredoc_fd != -1)
			close(heredoc->heredoc_fd);
		error(cmd, "pipe failed\n", 1);
	}
	else if (err == 2)
	{
		close_all_fd(pipe_fd_h);
		if (heredoc->heredoc_fd != -1)
			close(heredoc->heredoc_fd);
		error(cmd, "fork failed", 1);
	}
}
