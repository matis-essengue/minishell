/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:26:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/03 11:03:01 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// volatile sig_atomic_t	g_signal;

// void	handle_interactive_signal(void)
// {
// 	t_sa	sa;

// 	sa.sa_handler = handle_sigint;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	handle_exec_signal(void)
// {
// 	t_sa	sa;

// 	sa.sa_handler = exec_handle_sigint;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, handle_sigquit);
// }

// void	handle_child_signal(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }