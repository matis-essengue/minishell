/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/09/03 11:28:54 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	void_silenced_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	check_exit(t_cmd *cmd, int exit_status)
{
	if (!cmd)
		return ;
	if (!cmd->next && cmd->args)
	{
		if (cmd->args[0] && is_built_in(cmd))
			if (ft_strncmp(cmd->name, "exit", 4) == 0)
			{
				exit_status = built_in_exit(cmd, 0);
				exit(exit_status);
			}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_env	*my_env;
	char	*line;

	my_env = init_env(envp);
	if (!my_env)
		return (1);
	void_silenced_args(argc, argv);
	printf("\033[2J\033[H");
	while (1)
	{
		line = readline("\033[36mminishell> \033[0m");
		if (line == NULL)
			break ;
		add_history(line);
		cmd = parse(line, my_env);
		check_exit(cmd, 0);
		my_env->exit_status = execute_command(cmd, my_env);
		free(line);
	}
	free_my_env(my_env);
	return (0);
}
