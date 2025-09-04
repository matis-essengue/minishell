/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:24:49 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/04 15:39:09 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

char	**get_path(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (path == NULL)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_var_path(char **envp, char *var)
{
	int	i;
	int	len;

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
