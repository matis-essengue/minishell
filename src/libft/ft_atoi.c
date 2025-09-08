/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:49:53 by messengu          #+#    #+#             */
/*   Updated: 2024/11/26 10:07:13 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	mult;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		mult = -1;
	else
		mult = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * mult);
}

// int main()
// {
// 	// test 1
// 	char str[] = "12345";
// 	printf("%d\n", ft_atoi(str));

// 	// test 2
// 	char str2[] = "-12345yg   ";
// 	printf("%d\n", ft_atoi(str2));

// 	// test 3
// 	char str3[] = "         12345njl";
// 	printf("%d\n", ft_atoi(str3));

// 	return 0;
// }
