/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:50:43 by matis             #+#    #+#             */
/*   Updated: 2025/09/12 12:43:20 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal;

void	handle_sigint(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal == 0)
		rl_redisplay();
}

void	handle_sigint_in_exec(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigquit(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_signals(int interactive)
{
	if (interactive)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, &handle_sigint_in_exec);
		signal(SIGQUIT, &handle_sigquit);
	}
}
