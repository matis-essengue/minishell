/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:54 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/12 12:40:17 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	is_valid_number(char *str)
{
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+'
			&& str[i] != 32)
			return (2);
		if (str[i] == '-' || str[i] == '+')
		{
			sign++;
			if (sign > 1)
				return (2);
		}
		i++;
	}
	return (0);
}

int	check_long(char *str)
{
	long long	nb;
	long long	min;

	nb = 0;
	min = -9223372036854775807LL;
	if (ft_strlen(str) > 20)
		return (1);
	nb = ft_atoll(str);
	if (nb >= 9223372036854775807 || nb <= min)
		return (1);
	return (0);
}

long long	ft_atoll(char *str)
{
	long long	i;
	long long	res;
	int			neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * neg);
}
