/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/09 16:19:17 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	manage_no_cmd_with_an_outfile(t_cmd *cmd)
{
	int prev_old_fd;

	prev_old_fd = dup(FD_STDOUT);
	open_outfile(cmd);
	dup2(prev_old_fd, FD_STDOUT);
	close(prev_old_fd);
}

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
		printf("here\n");
		file = file->next;
	}
}
