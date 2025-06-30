/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:27:07 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/30 17:14:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// bien adapte les sorties et entrees avec les enum

void    manage_infile(t_cmd *cmd, int *pipefd)
{
    if (is_first()) 
    {
        close(pipefd[WRITE]);
        dup2(pipefd[READ], STDIN_FILENO);
        close(pipefd[READ]);
    }
    int fd;
    t_file *file;

    file = cmd->infile;
    while (file)
    {
        fd = open(file->name, O_RDONLY);
        if (fd == -1)
            return (error("infile open failed\n", 1));
        dup2(fd, STDIN_FILENO);
        close(fd);
        file = file->next;
    }
}
// revoir la gestion des heredocs et append

void    manage_outfile(t_cmd *cmd, int *pipefd)
{
    int fd;
    t_file *file;

    if () 
    {
        close(pipefd[READ]);
        dup2(pipefd[WRITE], STDOUT_FILENO);
        close(pipefd[WRITE]);
    }
    file = cmd->outfile;
    while (file)
    {
        fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            error("outfile open failed", 1);
            return;
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        file = file->next;
    }
}
