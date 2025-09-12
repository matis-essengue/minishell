/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:06:05 by matis             #+#    #+#             */
/*   Updated: 2025/09/12 12:43:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
}

void	handle_signal_heredoc(int signal)
{
	g_signal = signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
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
