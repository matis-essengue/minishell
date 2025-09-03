/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:22:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/03 11:33:03 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	free_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*tmp_h;

	if (!heredocs)
		return ;
	tmp_h = NULL;
	while (heredocs)
	{
		tmp_h = heredocs->next;
		if (heredocs->delimiter)
			free(heredocs->delimiter);
		if (heredocs->content)
			free(heredocs->content);
		if (heredocs->heredoc_fd != -1)
			close(heredocs->heredoc_fd);
		free(heredocs);
		heredocs = tmp_h;
	}
}

void	free_infile(t_cmd *cmd)
{
	t_file	*tmp;

	if (!cmd->infile)
		return ;
	tmp = NULL;
	while (cmd->infile)
	{
		tmp = cmd->infile->next;
		free(cmd->infile->name);
		if (cmd->infile->fd != -1)
			close(cmd->infile->fd);
		free(cmd->infile);
		cmd->infile = tmp;
	}
}

void	free_outfile(t_cmd *cmd)
{
	t_file	*tmp;

	if (!cmd->outfile)
		return ;
	tmp = NULL;
	while (cmd->outfile)
	{
		tmp = cmd->outfile->next;
		free(cmd->outfile->name);
		if (cmd->outfile->fd != -1)
			close(cmd->outfile->fd);
		free(cmd->outfile);
		cmd->outfile = tmp;
	}
}

void	free_all_struct(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	tmp = NULL;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->infile)
			free_infile(cmd);
		if (cmd->outfile)
			free_outfile(cmd);
		if (cmd->heredocs)
			free_heredocs(cmd->heredocs);
		if (cmd->name)
			free(cmd->name);
		if (cmd->args)
			free_array(cmd->args);
		if (cmd->pipefd[READ] != -1 || cmd->pipefd[WRITE] != -1)
			close_all_fd(cmd->pipefd);
		free(cmd);
		cmd = tmp;
	}
}

void	error(t_cmd *cmd, char *str, int code)
{
	free_all_struct(cmd);
	perror(str);
	exit(code);
}
