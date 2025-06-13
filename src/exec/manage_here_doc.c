/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:30:11 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/13 18:38:15 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

bool	compare_without_backslash(t_data *data, char *line)
{
	int len;
	
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strncmp(line, data->limiter, ft_strlen(line)) == 0)
	{
		free(line);
		return (true);
	}
	line[len - 1] = '\n';
	return (false);
}

void	manage_here_doc(t_data *data)
{
	char *line;
	int pipefd[2];

	if (pipe(pipefd) == -1)
		error("pipe failed\n", 1);
	while (1)
	{
		ft_putstr("here_doc>");
		line = get_next_line(FD_STDIN);
		if (line == NULL)
			break ;
		if (compare_without_backslash(data, line) == true)
			break ;
		// if (here_doc->append)
		// 	line = parse_heredoc(line);
		write(pipefd[WRITE], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[WRITE]);
	dup2(pipefd[READ], FD_STDIN);
	close(pipefd[READ]);
}
