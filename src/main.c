/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/09/12 12:28:52 by armosnie         ###   ########.fr       */
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
	rl_clear_history();
	if (cmd)
		free_all_struct(cmd);
	free_my_env(my_env);
	exit(0);
}

t_env	*first_preparation(char **envp)
{
	t_env	*my_env;

	if (!isatty(0))
		return (printf("minishell: tty required\n"), NULL);
	my_env = init_env(envp);
	if (!my_env)
		return (NULL);
	return (my_env);
}

void	clean_cmd(t_cmd *cmd, t_env *my_env)
{
	my_env->exit_status = execute_command(cmd, my_env);
	free_all_struct(cmd);
	cmd = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_env	*my_env;
	char	*line;

	void_silenced_args(argc, argv);
	my_env = first_preparation(envp);
	if (!my_env)
		return (1);
	cmd = NULL;
	handle_signals(1);
	printf("\033[2J\033[H");
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (!line)
			exit_and_free(my_env, cmd);
		add_history(line);
		if (cmd)
			free_all_struct(cmd);
		cmd = parse(line, my_env);
		if (cmd != NULL)
			clean_cmd(cmd, my_env);
		cmd = NULL;
	}
	return (free_my_env(my_env), 0);
}
