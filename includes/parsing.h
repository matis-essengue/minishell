/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:32:41 by messengu          #+#    #+#             */
/*   Updated: 2025/06/10 18:32:22 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECT_OP,
	TOKEN_CONTROL_OP,
}	t_token_type;

typedef struct s_token
{
	char	*value;
	int		type;
	struct s_token	*next;
}	t_token;

t_token		*tokenize(char *line);
t_token		*create_token(char *value, int type);
void		add_token(t_token **tokens, t_token *token);
char		*ft_strndup(const char *s1, int n);
const char	*get_token_type_str(int type);
void		free_tokens(t_token *tokens);
int			check_tokens(t_token *tokens);
int			is_meta_char(char c);
int			is_whitespace(char c);

#endif
