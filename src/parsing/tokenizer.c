/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:24:25 by messengu          #+#    #+#             */
/*   Updated: 2025/09/09 14:06:08 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

/**
 * @brief Add a pipe token to the tokens list
 *
 * @param start The first pipe character in the line
 * @param tokens The list of tokens
 * @param line The current line
 */
static void	add_pipe(char **start, t_token **tokens, char **line)
{
	t_token	*current_token;

	current_token = create_token(ft_strndup(*start, 1), TOKEN_CONTROL_OP);
	add_token(tokens, current_token);
	*start = *line;
}

/**
 * @brief Add a redirect token to the tokens list
 *
 * @param start The first redirect character in the line
 * @param tokens The list of tokens
 * @param i The number of characters to add
 */
static void	add_redirect(char **start, t_token **tokens, int i)
{
	t_token	*current_token;

	current_token = create_token(ft_strndup(*start, i), TOKEN_REDIRECT_OP);
	add_token(tokens, current_token);
}

/**
 * @brief Add a meta character to the tokens list
 * (either a pipe or a redirect)
 *
 * @param line The current line
 * @param tokens The list of tokens
 */
static void	add_meta_char(char **line, t_token **tokens)
{
	int		i;
	char	*start;
	char	meta_char;

	i = 0;
	start = *line;
	meta_char = **line;
	while (**line && **line == meta_char)
	{
		if (**line == '|')
			add_pipe(&start, tokens, line);
		else
		{
			i++;
			if (i == 2)
			{
				add_redirect(&start, tokens, i);
				start = *line;
				i = 0;
			}
		}
		(*line)++;
	}
	if (i != 0)
		add_redirect(&start, tokens, i);
}

/**
 * @brief Add a word to the tokens list
 *
 * @param line The current line
 * @param tokens The list of tokens
 */
static int	add_word(char **line, t_token **tokens)
{
	char	*i;
	char	quote;
	t_token	*current_token;

	i = *line;
	quote = 0;
	while (**line)
	{
		if (**line == '\'' || **line == '"')
		{
			if (quote && quote == **line)
				quote = 0;
			else if (!quote)
				quote = **line;
		}
		if (!quote && (is_meta_char(**line) || is_whitespace(**line)))
			break ;
		(*line)++;
	}
	current_token = create_token(ft_strndup(i, *line - i), TOKEN_WORD);
	add_token(tokens, current_token);
	if (quote)
		return (0);
	return (1);
}

/**
 * @brief Tokenize the line
 *
 * @param line The line to tokenize
 * @return The list of tokens
 */
t_token	*tokenize(char *line)
{
	t_token	*tokens;
	char	*line_ptr;

	tokens = NULL;
	line_ptr = line;
	while (*line_ptr)
	{
		if (*line_ptr && is_whitespace(*line_ptr))
			while (*line_ptr && is_whitespace(*line_ptr))
				line_ptr++;
		else if (*line_ptr && is_meta_char(*line_ptr))
			add_meta_char(&line_ptr, &tokens);
		else if (*line_ptr && !is_meta_char(*line_ptr))
		{
			if (!add_word(&line_ptr, &tokens))
			{
				printf("minishell: syntax error: unclosed quote\n");
				return (NULL);
			}
		}
		else
			line_ptr++;
	}
	return (tokens);
}
