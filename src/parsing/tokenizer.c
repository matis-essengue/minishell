/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:24:25 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 10:30:17 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static int	is_meta_char(char c)
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

static void	add_meta_char(char **line, t_token **tokens)
{
	int		i;
	char	*start;
	char	meta_char;
	t_token	*current_token;

	i = 0;
	start = *line;
	meta_char = **line;
	while (**line && **line == meta_char)
	{
		if (**line == '|')
		{
			current_token = create_token(ft_strndup(start, 1), TOKEN_CONTROL_OP);
			add_token(tokens, current_token);
			start = *line;
		}
		else
		{
			i++;
			if (i == 2)
			{
				current_token = create_token(ft_strndup(start, 2), TOKEN_REDIRECT_OP);
				add_token(tokens, current_token);
				start = *line;
				i = 0;
			}
		}
		(*line)++;
	}
	if (i != 0)
	{
		current_token = create_token(ft_strndup(start, i), TOKEN_REDIRECT_OP);
		add_token(tokens, current_token);
	}
}

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
		if (!quote && (is_meta_char(**line) || **line == ' ' || **line == '\t' || **line == '\n'))
			break;
		(*line)++;
	}
	current_token = create_token(ft_strndup(i, *line - i), TOKEN_WORD);
	add_token(tokens, current_token);
	if (quote)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (0);
	}
	return (1);
}

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	char	*line_ptr;

	tokens = NULL;
	line_ptr = line;
	while (*line_ptr)
	{
		if (*line_ptr && (*line_ptr == ' ' || *line_ptr == '\t' || *line_ptr == '\n'))
			while (*line_ptr && (*line_ptr == ' ' || *line_ptr == '\t' || *line_ptr == '\n'))
				line_ptr++;
		else if (*line_ptr && is_meta_char(*line_ptr))
			add_meta_char(&line_ptr, &tokens);
		else if (*line_ptr && !is_meta_char(*line_ptr))
		{
			if (!add_word(&line_ptr, &tokens))
				return (NULL);
		}
		else
			line_ptr++;
	}
	return (tokens);
}
