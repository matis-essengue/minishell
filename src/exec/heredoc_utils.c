/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:17:33 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/12 14:40:58 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

t_heredoc	*get_last_heredoc(t_cmd *cmd)
{
	t_heredoc	*heredoc;

	if (!cmd || !cmd->heredocs)
		return (NULL);
	heredoc = cmd->heredocs;
	while (heredoc->next)
		heredoc = heredoc->next;
	return (heredoc);
}

void	unused_heredoc_fd(t_cmd *current, t_cmd *cmd_list)
{
	t_cmd		*tmp;
	t_heredoc	*heredoc;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp != current)
		{
			heredoc = tmp->heredocs;
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
		tmp = tmp->next;
	}
}

int	check_heredoc_total(t_cmd *cmd)
{
	int			count;
	t_cmd		*tmp;
	t_heredoc	*heredoc;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		heredoc = tmp->heredocs;
		while (heredoc)
		{
			count++;
			heredoc = heredoc->next;
		}
		tmp = tmp->next;
	}
	if (count > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		return (2);
	}
	return (0);
}
