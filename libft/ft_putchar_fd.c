/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:25:49 by matis             #+#    #+#             */
/*   Updated: 2024/11/26 11:15:39 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

// int	main(void)
// {
// 	// Test 1 : Afficher un caractère sur la sortie standard
// 	ft_putchar_fd('A', 1);
// 	write(1, "\n", 1);

// 	// Test 2 : Afficher un caractère sur la sortie d'erreur
// 	ft_putchar_fd('B', 2);
// 	write(2, "\n", 1);

// 	// Test 3 : Test avec un descripteur de fichier invalide
// 	ft_putchar_fd('C', -1);

// 	// Test 4 : Afficher un caractère nul (non visible)
// 	ft_putchar_fd('\0', 1);
// 	write(1, "\n", 1);

// 	return (0);
// }
