/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/06/16 16:47:24 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	// t_cmd *cmds;

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
		pipe_function(cmd, envp);
		free(line);
	}
	// parse(argv[1]);

    return (0);
}
