/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:27:07 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/16 12:46:05 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

// bien adapte les sorties et entrees avec les enum

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
// revoir la gestion des heredocs et append

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
        // if (here_doc->append)
		// 	line = parse_heredoc(line);
        if (cmd->heredocs)
        fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return (error("outfile error\n", 1));
    }
    dup2(fd, FD_STDOUT);
    close(fd);
}
