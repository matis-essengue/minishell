/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/06/20 15:57:24 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	// printf("final res : %d\n", res);
	return (res);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
	t_cmd *cmd;
	printf("\033[2J\033[H");
	char *line;
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (line == NULL)
			break;
		add_history(line);
		cmd = parse(line);
		printf("count cmd %d\n", count_cmd(cmd));
		printf("count cmd and args %d\n", count_cmd_args(cmd));
		pipe_function(cmd, envp);
		free(line);
	}
    return (0);
}
