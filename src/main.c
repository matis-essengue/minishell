/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:54:53 by messengu          #+#    #+#             */
/*   Updated: 2025/05/26 17:36:42 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
// 	t_stack *stack;

	(void)argc;
	(void)argv;
	(void)envp;
// 	stack = parse(arg);
// 	while (!is_empty(stack))
// 	{
// 		cmd = pop(&stack);
// 		execute(cmd);
// 		free_cmd(cmd);
// 	}
// 	clean(&stack);
	parse(argv[1]);

    return (0);
}
