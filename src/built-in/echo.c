/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:26 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/11 14:51:54 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	cmp_n(char *s1)
{
	int i;

	i = 1;
	if (s1[0] != '-')
		return (1);
	while (s1[i] && s1[i] == 'n')
		i++;
	if (s1[i] != '\0')
		return (1);
	return (0);
}

int	n_search(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (cmp_n(args[i]) == 0)
			i++;
		else
			break ;
	}
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
	if (cmd->args && cmd->args[i] && cmp_n(cmd->args[i]) == 0)
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
			write(1, " ", 1);
		i++;
	}
	if (newline == 1)
		printf("\n");
	return (0);
}
