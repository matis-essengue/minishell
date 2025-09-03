/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:32:41 by messengu          #+#    #+#             */
/*   Updated: 2025/09/03 11:22:21 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_file	t_file;
typedef struct s_env	t_env;

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



t_token					*tokenize(char *line);
t_token					*create_token(char *value, int type);
void					add_token(t_token **tokens, t_token *token);
char					*ft_strndup(const char *s1, int n);
const char				*get_token_type_str(int type);
void					free_tokens(t_token *tokens);
int						check_tokens(t_token *tokens);
int						is_meta_char(char c);
int						is_whitespace(char c);
void					allocate_and_fill_args(t_cmd *cmd, t_token *tokens, int arg_count);
t_token					*process_redirections(t_cmd *cmd, t_token *tokens, t_file **start_infile, t_file **start_outfile);
void					reset_file_pointers(t_cmd *cmd, t_file **start_infile, t_file **start_outfile);
void					handle_input_redirect(t_cmd *cmd, t_token *current, t_file **start_infile);
void					handle_output_redirect(t_cmd *cmd, t_token *current, t_file **start_outfile);
t_cmd					*tokens_to_cmds(t_token *tokens);
void					expand_cmds(t_cmd *tokens, t_env *env);
void					remove_quotes(t_cmd *cmds);

#endif
