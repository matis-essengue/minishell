/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:07:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/03 11:40:16 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	invalid_option(char **args, char *str)
{
	if (args)
	{
		if ((args[0][0] == '-' && args[0][1])
			|| (args[0][0] == '-' && !args[0][1]))
		{
			if (ft_strncmp(str, "env", 3) == 0)
				return (2);
			if (ft_strncmp(str, "pwd", 3) == 0)
				return (2);
			if (ft_strncmp(str, "export", 6) == 0)
				return (2);
			if (ft_strncmp(str, "unset", 5) == 0)
				return (2);
			if (ft_strncmp(str, "exit", 4) == 0)
				return (2);
		}
	}
	return (0);
}

int	env_len(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = envp;
	if (!tmp || !tmp[i])
		return (0);
	while (tmp[i])
		i++;
	return (i);
}

char	*find_var(char *target_var, char **env)
{
	int	i;
	int	len;
	int equal_len;
	char *ret_path;

	i = 0;
	ret_path = NULL;
	len = ft_strlen(target_var);
	equal_len = 0;
	while (target_var[equal_len] && target_var[equal_len] != '=')
		equal_len++;
	while (env[i])
	{
		if (ft_strncmp(env[i], target_var, len) == 0)
		{
			ret_path = ft_strdup(&env[i][equal_len + 1]);
			if (!ret_path)
				return (NULL);
			return (ret_path + equal_len + 1);
		}
		i++;
	}
	return (NULL);
}

int 	return_char_pos(char *str, char c)
{
	int i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	check_is_same_var(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = return_char_pos(s1, '=');
	len_s2 = return_char_pos(s2, '=');
	if (len_s1 == 0 || len_s2 == 0)
		return (0);
	if (ft_strncmp(s1, s2, len_s1) == 0
		&& len_s2 == len_s1)
		return (1);
	return (0);
}
