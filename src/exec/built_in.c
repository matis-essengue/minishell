/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:48:50 by armosnie          #+#    #+#             */
/*   Updated: 2025/07/31 14:56:08 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

bool    is_built_in(char *cmd)
{
    if (cmd == NULL)
        return (false);
    if (ft_strcmp(cmd, "echo") == 0)
        return (true);
     if (ft_strcmp(cmd, "cd") == 0)
        return (true);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (true);
    if (ft_strcmp(cmd, "export") == 0)
        return (true);
    if (ft_strcmp(cmd, "unset") == 0)
        return (true);
    if (ft_strcmp(cmd, "env") == 0)
        return (true);
    if (ft_strcmp(cmd, "exit") == 0)
        return (true);
    return (false);
}

