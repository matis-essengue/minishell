/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:06 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/20 16:14:03 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

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

// void    print_tab()

char    **recup_full_cmd(t_cmd *cmd)
{
    char **full_cmd;
    int i;
    int j;

    i = 0;
    full_cmd = malloc(sizeof(char *) * (count_cmd_args(cmd) + 1));
    if (full_cmd == NULL)
        return (NULL);
    if (cmd->name)
        full_cmd[i] = cmd->name;
    i++;
    j = 0;
    cmd->args = malloc(sizeof(char * ) * 4);
    cmd->args[0] = "proutenflame";
    printf("%s\n", cmd->args[0]);
    // while (cmd->args[j])
    // {
    //     printf("----------caca");
    //     full_cmd[i] = cmd->args[j];
    //     i++;
    //     j++;
    // }
    full_cmd[i] = NULL;
    // print_tab(full_cmd);
    return (full_cmd);
}

bool    exe_my_cmd(t_cmd *cmd, char **envp)
{
    char **path;
    char **full_cmd;

    full_cmd = recup_full_cmd(cmd);
    if (full_cmd == NULL || full_cmd[0] == NULL)
        return (free_array(full_cmd), false);
    if (access(full_cmd[0], F_OK | X_OK) == 0)
		execve(full_cmd[0], full_cmd, envp);
    path = get_path(envp);
    if (path == NULL)
    {
        free_array(full_cmd);
        free_array(path);
        error("env error", 127);
    }
    exec(full_cmd[0], full_cmd, path, envp);
    free_array(path);
    free_array(full_cmd);
    error("command not found", 127);
    return (false);
}
