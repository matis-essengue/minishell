/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:06 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/04 16:11:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char    **get_path(char **envp)
{
    char **path;
    int     i;

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
    error("path not found", 1);
    return (NULL);
}

char    *join_slash(char *path, char *cmd_cut)
{
    char *slash;
    char *full_path;

    slash = ft_strjoin(path, "/");
    if (slash == NULL)
        return (NULL);
    full_path = ft_strjoin(slash, cmd_cut);
    if (full_path == NULL)
        return (NULL);
    free(slash);
    return (full_path);
}

void    exec(char *cmd_cut, char **cmd, char **path, char **envp)
{
    int i;
    char *full_path;
    
    i = 0;
    while (path[i])
    {
        full_path = join_slash(path[i], cmd_cut);
        if (full_path == NULL)
            return ;
        if (access(path[i], F_OK | X_OK) == 0)
            execve(full_path, cmd, envp);
        free(full_path);
        i++;
    }
}

bool    exe_my_cmd(char *cmd, char **envp)
{
    char **cmd_cut;
    char **path;
    
    cmd_cut = ft_split(cmd, ' ');
    if (cmd_cut == NULL || cmd_cut[0] == NULL)
        return (free_array(cmd_cut), false);
    if (access(cmd_cut[0], F_OK | X_OK) == 0)
		execve(cmd_cut[0], cmd_cut, envp);
    path = get_path(envp);
    if (path == NULL)
    {
        free_array(cmd_cut);
        free_array(path);
        error("env error", 127);
    }
    exec(cmd_cut[0], cmd_cut, path, envp);
    free_array(path);
    free_array(cmd_cut);
    error("command not found", 127);
    return (false);
}
