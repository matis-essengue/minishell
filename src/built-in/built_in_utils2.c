/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:24:49 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/03 15:15:58 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// int 	return_before_equal(char *str)
// {
// 	int i;

// 	i = 0;
// 	if (!str || !str[i])
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] && str[i + 1] && str[i + 1] == '=')
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

char	*get_var_path(char **envp, char *var)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var);
	if (len == 0)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
			return (ft_strdup(envp[i]));
		i++;
	}
	return (NULL);
}