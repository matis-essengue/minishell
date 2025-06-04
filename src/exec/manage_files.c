/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:27:07 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/04 16:11:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void    manage_infile(t_data *data, int *pipefd)
{
    int fd;

    close(pipefd[READ]);
    dup2(pipefd[WRITE], STDOUT);
    close(pipefd[WRITE]);
    if (data->here_doc == false)
    {
        fd = open(data->infile, O_RDONLY);
        if (fd == -1)
            return (error("infile error\n", 1));
        dup2(fd, STDIN);
        close(fd);
    }
}

void    manage_outfile(t_data *data, int *pipefd)
{
    int fd;
    
    close(pipefd[WRITE]);
    dup2(pipefd[WRITE], STDIN);
    close(pipefd[READ]);
    if (data->here_doc == false)
    {
        fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (error("outfile error\n", 1));
    }
    else
    {
        fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
            return (error("outfile error\n", 1));
    }
    dup2(fd, STDOUT);
    close(fd);
}