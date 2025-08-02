/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/07/31 16:36:19 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_cmd *cmd;

	(void)argc;
	(void)argv;
	printf("\033[2J\033[H");
	char *line;
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (line == NULL)
			break;
		add_history(line);
		cmd = parse(line);
		// handle_signals(); ici les signaux ?
		pipe_function(cmd, envp);
		free(line);
	}
    return (0);
}
