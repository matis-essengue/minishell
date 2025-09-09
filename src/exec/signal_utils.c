/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:06:05 by matis             #+#    #+#             */
/*   Updated: 2025/09/09 15:31:55 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

volatile sig_atomic_t	g_signal;

void	handle_sigint(int signal)
{
	g_signal = signal;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_in_exec(int signal)
{
	g_signal = signal;
	// rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigquit(int signal)
{
	struct sigaction act;
	
	ft_bzero(&act, sizeof(act));
	act.sa_handler = signal_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

