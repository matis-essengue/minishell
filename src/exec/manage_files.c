/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:27:07 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/13 18:37:56 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

void    manage_infile(t_cmd *cmd, int *pipefd)
{
    int fd;

    close(pipefd[READ]);
    dup2(pipefd[WRITE], FD_STDOUT);
    close(pipefd[WRITE]);
    if (cmd->heredocs == false)
    {
        fd = open(cmd->infile, O_RDONLY | O_CREAT);
        if (fd == -1)
            return (error("infile error\n", 1));
        dup2(fd, FD_STDIN);
        close(fd);
    }
}

void    manage_outfile(t_cmd *cmd, int *pipefd)
{
    int fd;
    
    close(pipefd[WRITE]);
    dup2(pipefd[WRITE], FD_STDIN);
    close(pipefd[READ]);
    if (cmd->heredocs == false)
    {
        fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (error("outfile error\n", 1));
    }
    else
    {
        fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return (error("outfile error\n", 1));
    }
    dup2(fd, FD_STDOUT);
    close(fd);
}