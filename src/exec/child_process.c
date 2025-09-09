/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:46:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/08 17:53:55 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	files_and_management(t_cmd *cmd, t_cmd *cmd_list, int prev_read_fd)
{
	t_heredoc *last_hd;

	unused_heredoc_fd(cmd, cmd_list);
	last_hd = get_last_heredoc(cmd);
	if (last_hd && last_hd->heredoc_fd != -1)
	{
		dup2(last_hd->heredoc_fd, FD_STDIN);
		close(last_hd->heredoc_fd);
	}
	else if (cmd->infile && cmd->infile->name)
		open_infile(cmd);
	else if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, FD_STDIN);
		close(prev_read_fd);
	}
	if (cmd->outfile && cmd->outfile->name)
		open_outfile(cmd);
}

void	child_call(t_cmd *cmd, t_cmd *cmd_list, t_env *env, int prev_read_fd)
{
	int	exit_status;

	child_signal_handler();
	files_and_management(cmd, cmd_list, prev_read_fd);
	if (cmd->output_type == PIPEOUT)
	{
		close(cmd->pipefd[READ]);
		dup2(cmd->pipefd[WRITE], FD_STDOUT);
		close(cmd->pipefd[WRITE]);
	}
	if (is_built_in(cmd))
	{
		exit_status = child_process_built_in(cmd, env);
		exit(exit_status);
	}
	exe_my_cmd(cmd, env);
}

int	wait_child(pid_t *pid, int size)
{
	int	i;
	int	status;

	i = 0;
	while (i < size)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}
