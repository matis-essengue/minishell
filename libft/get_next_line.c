/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:50:20 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/17 16:22:59 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_buffer(char *str, char *buffer)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = malloc(ft_strlen_opti(str) + ft_strlen_opti(buffer) + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		new_str[i + j] = buffer[j];
		j++;
	}
	free(str);
	new_str[i + j] = '\0';
	return (new_str);
}

void	clear_buffer(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	j = 0;
	while (buffer[j + i])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	char		*line;
	int			size_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_strndup_gnl(buffer, '\0');
	size_read = BUFFER_SIZE;
	while (size_read == BUFFER_SIZE && search_char(buffer, '\n') == 0)
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read == -1)
			return (buffer[0] = '\0', free(str), NULL);
		buffer[size_read] = '\0';
		str = add_buffer(str, buffer);
		if (str == NULL)
			return (NULL);
	}
	if (str[0] == '\0')
		return (free(str), NULL);
	line = ft_strndup_gnl(str, '\n');
	free(str);
	clear_buffer(buffer);
	return (line);
}
// #include <stdio.h>
// int	main(int ac, char **av)
// {
// 	int fd;
// 	char *line;

// 	(void)ac;
// 	fd = open(av[1], O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		ft_printf(">%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }