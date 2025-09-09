/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/09/08 17:56:21 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	void_silenced_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	exit_and_free(t_env *my_env)
{
	free_my_env(my_env);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_env	*my_env;
	char	*line;

	void_silenced_args(argc, argv);
	if (!isatty(0))
		return (printf("minishell: tty required\n"), 1);
	my_env = init_env(envp);
	if (!my_env)
		return (1);
	cmd = NULL;
	void_silenced_args(argc, argv);
	interactive_signal_handler();
	printf("\033[2J\033[H");
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (!line)
			exit_and_free(my_env);
		add_history(line);
		cmd = parse(line, my_env);
		my_env->exit_status = execute_command(cmd, my_env);
	}
	return (free_my_env(my_env), 0);
}
