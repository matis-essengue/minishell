/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:17:33 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/11 14:31:15 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

t_heredoc	*get_last_heredoc(t_cmd *cmd)
{
	t_heredoc *heredoc;
	
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
