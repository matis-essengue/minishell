/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:52:40 by matis             #+#    #+#             */
/*   Updated: 2025/09/08 16:20:51 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	save_termios(struct termios *out_saved)
{
	if (tcgetattr(STDIN_FILENO, out_saved) == -1)
	{
		perror("tcgetattr");
		return (-1);
	}
	return (0);
}

void	restore_termios(const struct termios *saved)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, saved) == -1)
	{
		perror("tcsetattr");
	}
}
