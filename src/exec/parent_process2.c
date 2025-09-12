/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:28:53 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/12 14:34:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	pipe_check_or_create(t_cmd *cmd, pid_t *pid, int i, int prev_read_fd)
{
	if (cmd->output_type == PIPEOUT && pipe(cmd->pipefd) == -1)
	{
		if (prev_read_fd != -1)
			close(prev_read_fd);
		error(cmd, "pipe failed", 1);
	}
	pid[i] = fork();
	pidarray_check(cmd, pid, prev_read_fd, i);
}

void	pidarray_check(t_cmd *cmd, pid_t *pid, int prev_read_fd, int i)
{
	if (pid[i] == -1)
	{
		if (prev_read_fd != -1)
			close(prev_read_fd);
		if (cmd->output_type == PIPEOUT)
		{
			close_all_fd(cmd->pipefd);
			error(cmd, "fork failed", 1);
		}
	}
}

int	single_heredoc(t_cmd *cmd, t_cmd *first_cmd, t_env *env, int prev_read_fd)
{
	t_heredoc	*heredoc;

	if (!cmd->name)
	{
		if (cmd->heredocs)
		{
			manage_heredocs(cmd, first_cmd, prev_read_fd, env);
			heredoc = cmd->heredocs;
			while (heredoc)
			{
				if (heredoc->heredoc_fd != -1)
				{
					close(heredoc->heredoc_fd);
					heredoc->heredoc_fd = -1;
				}
				heredoc = heredoc->next;
			}
		}
		return (1);
	}
	return (0);
}
