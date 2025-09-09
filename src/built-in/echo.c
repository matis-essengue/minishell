/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:26 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/09 20:37:14 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	n_search(char **args)
{
	int	i;

	i = 0;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	return (i);
}

int	write_sentance(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		ret = write(1, &str[i], 1);
		if (ret == -1)
			return (1);
		i++;
	}
	return (0);
}

int	built_in_echo(t_cmd *cmd)
{
	int	newline;
	int	i;

	i = 0;
	if (cmd->args && cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i = n_search(cmd->args);
	}
	else
		newline = 1;
	while (cmd->args && cmd->args[i])
	{
		if (write_sentance(cmd->args[i]) == 1)
			return (perror("minishell: echo"), 1);
		if (cmd->args[i + 1])
			if (printf(" ") < 0)
				return (1);
		i++;
	}
	if (newline == 1)
		printf("\n");
	return (0);
}
