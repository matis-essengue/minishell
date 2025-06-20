/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:19:43 by messengu          #+#    #+#             */
/*   Updated: 2025/06/20 16:02:20 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/exec.h"
# include "../includes/parsing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

// ---- STRUCTS ENUM ----

typedef enum input_type
{
	STDIN = 0,
	PIPEIN = 0,
	HERE_DOC,
}						t_input_type;

typedef enum output_type
{
	STDOUT = 1,
	PIPEOUT = 1,
}						t_output_type;

// ---- STRUCTS ----

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	bool expand_vars; // parcing here_doc
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_file
{
	char				*name;
	char				permission[3];
	bool append; // pour ajouter true or false type
	struct s_file		*next;
}						t_file;

typedef struct s_cmd
{
	char				*name;
	char 				**args; // les options flag d'une commande
	t_file				*infile;
	t_file				*outfile;
	t_input_type		input_type;
	t_output_type		output_type;
	t_heredoc			*heredocs;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_stack
{
	void				*value;
	struct s_stack		*next;
}						t_stack;

t_cmd					*parse(char *line);
t_stack					*init_stack(void);
void					push(t_stack **stack, void *value);
void					*pop(t_stack **stack);
void					*top(t_stack *stack);
void					clean(t_stack **stack);
int						is_empty(t_stack *stack);
void					print_cmd(t_cmd *cmd);
int						check_cmds(t_cmd *cmd);
t_cmd					*tokens_to_cmds(t_token *tokens);
void					expand_cmds(t_cmd *tokens);
void					remove_quotes(t_cmd *cmds);

#endif
