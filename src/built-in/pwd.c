/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:20:01 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/09 11:57:06 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	built_in_pwd(t_cmd *cmd)
{
	char	*pwd;

	if (cmd->args && (ft_strncmp(cmd->args[0], "-", 1) == 0))
	{
		printf("pwd: There is no option\n");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("");
		return (1);
	}
	if (pwd)
		printf("%s\n", pwd);
	free(pwd);
	return (0);
}
