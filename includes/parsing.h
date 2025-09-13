/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:17:19 by messengu          #+#    #+#             */
/*   Updated: 2025/09/13 12:17:20 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_cmd		t_cmd;
typedef struct s_file		t_file;
typedef struct s_env		t_env;
typedef struct s_heredoc	t_heredoc;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIRECT_OP,
	TOKEN_CONTROL_OP,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_expand_state
{
	char	*result;
	int		i;
	int		start;
	int		squoted;
	int		dquoted;
}	t_expand_state;

t_token					*tokenize(char *line);
t_token					*create_token(char *value, int type);
void					add_token(t_token **tokens, t_token *token);
char					*ft_strndup(const char *s1, int n);
const char				*get_token_type_str(int type);
void					free_tokens(t_token *tokens);
int						check_tokens(t_token *tokens);
int						is_meta_char(char c);
int						is_whitespace(char c);
void					allocate_and_fill_args(t_cmd *cmd,
							t_token *tokens, int arg_count);
t_token					*process_redirections(t_cmd *cmd, t_token *tokens,
							t_file **start_infile, t_file **start_outfile);
void					reset_file_pointers(t_cmd *cmd,
							t_file **start_infile, t_file **start_outfile);
void					handle_input_redirect(t_cmd *cmd,
							t_token *current, t_file **start_infile);
void					handle_output_redirect(t_cmd *cmd,
							t_token *current, t_file **start_outfile);
t_cmd					*tokens_to_cmds(t_token *tokens);
void					expand_line(char **line, t_env *env);
void					remove_quotes(t_cmd *cmds);
char					*expand_variable(char *str,
							t_env *env, int *consumed, int is_escaped);
char					*join_and_free(char *s1, char *s2);
char					*_remove_quotes(char *word);
void					rm_quotes_for_all_files(t_file *first_file);
void					rm_quotes_for_all_heredocs(t_heredoc *first_heredoc);
void					init_cmd(t_cmd *cmd);
char					*finalize_quote_removal(char *new_word,
							char *start, char *end, char *word);
char					handle_quotes(char *temp,
							char quote, char **start, char **new_word);

#endif
