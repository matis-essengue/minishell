/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/09/04 13:47:17 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	void_silenced_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	check_exit(t_cmd *cmd, int exit_status, t_env *env)
{
	if (!cmd)
		return ;
	if (!cmd->next && cmd->args)
	{
		if (cmd->args[0] && is_built_in(cmd))
			if (ft_strncmp(cmd->name, "exit", 4) == 0)
			{
				exit_status = built_in_exit(cmd, 0, env);
				free_all_struct(cmd);
				free_my_env(env);
				exit(exit_status);
			}
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_all_struct(cmd);
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
	printf("\033[2J\033[H");
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (line == NULL)
			break ;
		add_history(line);
		cmd = parse(line, my_env);
		check_exit(cmd, 0, my_env); //handle quit signal ?
		my_env->exit_status = execute_command(cmd, my_env);
		free(line);
	}
	free_my_env(my_env);
	return (0);
}
