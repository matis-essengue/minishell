/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:47:40 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/04 15:34:46 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%d : %s\n", i, array[i]);
		i++;
	}
}

int	count_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_args(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	if (!tmp->args || !tmp)
		return (0);
	while (tmp->args && tmp->args[i])
		i++;
	return (i);
}

int	count_all_cmd_args(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count_arg;
	int		res;

	res = 0;
	tmp = cmd;
	if (tmp == NULL)
		return (0);
	while (tmp)
	{
		count_arg = 0;
		if (tmp->args)
		{
			while (tmp->args[count_arg])
			{
				res++;
				count_arg++;
			}
		}
		if (tmp->name)
			res++;
		tmp = tmp->next;
	}
	return (res);
}

void	unused_heredoc_fd(t_cmd *current, t_cmd *cmd_list)
{
	t_cmd		*tmp;
	t_heredoc	*heredoc;

	tmp = cmd_list;
	heredoc = tmp->heredocs;
	while (tmp != current && heredoc)
	{
		while (heredoc)
		{
			if (heredoc->heredoc_fd != -1)
				close(heredoc->heredoc_fd);
			heredoc = heredoc->next;
		}
		tmp = tmp->next;
	}
}
