/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:33:04 by messengu          #+#    #+#             */
/*   Updated: 2025/06/03 14:06:06 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

/**
 * @brief Duplicate a string up to n characters
 *
 * @param s1 The string to duplicate
 * @param n The number of characters to duplicate
 * @return The duplicated string
 */
char	*ft_strndup(const char *s1, int n)
{
	int		strlen;
	char	*dup;

	strlen = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * n + 1);
	if (!dup)
		return (NULL);
	strlen = 0;
	while (s1[strlen] && strlen < n)
	{
		dup[strlen] = s1[strlen];
		strlen++;
	}
	dup[strlen] = '\0';
	return (dup);
}

char	*get_input_type(t_cmd *cmd)
{
	if (cmd->input_type == PIPEIN)
		return ("PIPEIN");
	if (cmd->input_type == STDIN)
		return ("STDIN");
	if (cmd->input_type == HERE_DOC)
		return ("HEREDOC");
	return (NULL);
}

char	*get_output_type(t_cmd *cmd)
{
	if (cmd->output_type == PIPEOUT)
		return ("PIPEOUT");
	if (cmd->output_type == STDOUT)
		return ("STDOUT");
	return (NULL);
}

/**
 * @brief [DEBUG FUNCTION] Print a command
 * with its arguments
 *
 * @param cmd The command to print
 */
void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf("[NAME]: %s\n", cmd->name);
	if (cmd->args != NULL)
	{
		i = 0;
		printf("[ARGS]:");
		while (cmd->args[i])
		{
			printf(" %s", cmd->args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("[ARGS]: NULL\n");
	printf("[INFILE]:");
	if (cmd->infile != NULL)
	{
		while (cmd->infile)
		{
			printf("  > %s", cmd->infile->name);
			cmd->infile = cmd->infile->next;
		}
	}
	else
		printf(" NULL");
	printf("\n[OUTFILE]:");
	if (cmd->outfile)
	{
		while (cmd->outfile)
		{
			printf("  > %s", cmd->outfile->name);
			cmd->outfile = cmd->outfile->next;
		}
	}
	else
		printf(" NULL");
	printf("\n[OUTPUT_TYPE]: %s\n", get_output_type(cmd));
	printf("[INPUT_TYPE]: %s\n", get_input_type(cmd));
	printf("\n");
}

/**
 * @brief Check if a character is a meta character
 * (here only |, <, >)
 *
 * @param c The character to check
 * @return 1 if the character is a meta character, 0 otherwise
 */
int	is_meta_char(char c)
{
	const char	*meta_chars;

	meta_chars = "|<>";
	while (*meta_chars)
	{
		if (c == *meta_chars)
			return (1);
		meta_chars++;
	}
	return (0);
}

/**
 * @brief Check if a character is a whitespace character
 * (here only space, tab, newline)
 *
 * @param c The character to check
 * @return 1 if the character is a whitespace character, 0 otherwise
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
