/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:39 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/12 12:41:35 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	open_infile(t_cmd *cmd, t_cmd *cmd_list, t_env *env)
{
	t_file	*file;

	file = cmd->infile;
	if (!file || !file->name)
		return (perror(file->name), 1);
	while (file && file->name)
	{
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
		{
			perror(file->name);
			free_all_struct(cmd_list);
			free_my_env(env);
			exit(1);
		}
		dup2(file->fd, FD_STDIN);
		close(file->fd);
		file = file->next;
	}
	return (0);
}

void	open_outfile(t_cmd *cmd, t_cmd *cmd_list, t_env *env)
{
	t_file	*file;

	file = cmd->outfile;
	while (file && file->name)
	{
		if (file->append)
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->fd == -1)
		{
			perror(file->name);
			free_all_struct(cmd_list);
			free_my_env(env);
			exit(1);
		}
		dup2(file->fd, FD_STDOUT);
		close(file->fd);
		file = file->next;
	}
}
