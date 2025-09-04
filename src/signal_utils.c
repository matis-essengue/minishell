/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:06:05 by matis             #+#    #+#             */
/*   Updated: 2025/09/04 15:08:59 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	create_new_line(void)
{
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

static void	signal_handler_ignore(void)
{
	rl_on_new_line();
	rl_redisplay();
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
		create_new_line();
	else if (signal == SIGQUIT)
		signal_handler_ignore();
}

void	set_signal_action(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = signal_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
