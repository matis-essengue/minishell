/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/09/05 17:09:28 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	void_silenced_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	exit_and_free(t_env *my_env, t_cmd *cmd)
{
	free_my_env(my_env);
	if (cmd)
		free_all_struct(cmd);
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
	set_signal_action();
	printf("\033[2J\033[H");
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (!line)
			exit_and_free(my_env, cmd);
		add_history(line);
		cmd = parse(line, my_env);
		my_env->exit_status = execute_command(cmd, my_env);
		free(line);
	}
	return (free_my_env(my_env), 0);
}
