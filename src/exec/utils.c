/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:47:40 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/28 14:52:23 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	count_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	int count;
	
	count = 0;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_cmd_args(t_cmd *cmd)
{
	t_cmd *tmp;
	int count_arg;
	int res;
	
	res = 0;
	tmp = cmd;
	while (tmp)
	{
		count_arg = 0;
		if (tmp->args)
			while (tmp->args[count_arg])
			{
				res++;
				count_arg++;
			}
		if (tmp->name)
			res++;
		tmp = tmp->next;
	}
	return (res);
}
