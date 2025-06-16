/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/06/16 12:53:42 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
// 	t_stack *stack;

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
		pipe_function(cmd);
		free(line);
	}
	// parse(argv[1]);

    return (0);
}
