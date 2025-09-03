/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:34:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/03 10:52:26 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// void	handle_sigint(int sig)
// {
// 	g_signal = sig;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	exec_handle_sigint(int sig)
// {
// 	g_signal = sig;
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// }

// void	handle_sigquit(int sig)
// {
// 	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
// 	(void)sig;
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// }