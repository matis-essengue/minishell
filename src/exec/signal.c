/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:50:43 by matis             #+#    #+#             */
/*   Updated: 2025/09/09 18:56:10 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"


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

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
}



void	handle_signal_heredoc(int signal)
{
	g_signal = signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(130);
}

void	handle_heredoc_signals(void)	
{
	signal(SIGINT, &handle_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	parent_ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}