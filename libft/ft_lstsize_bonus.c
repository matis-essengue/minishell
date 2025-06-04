/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:20:33 by matis             #+#    #+#             */
/*   Updated: 2024/11/25 13:44:22 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*elem;

	size = 0;
	if (lst)
	{
		elem = lst;
		while (elem)
		{
			size++;
			elem = elem->next;
		}
	}
	return (size);
}
