/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:19:43 by messengu          #+#    #+#             */
/*   Updated: 2025/06/10 17:28:33 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../includes/parsing.h"

// ---- STRUCTS ----

typedef enum input_type
{
    STDIN,
    PIPEIN,
    HERE_DOC,
} t_input_type;

typedef enum output_type
{
    STDOUT,
    PIPEOUT,
} t_output_type;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	int					expand_vars;
	struct s_heredoc	*next;
} t_heredoc;

typedef struct s_file
{
	char			*name;
	char			permission[3];
	int				append;
	struct s_file	*next;
} t_file;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	t_file			*infile;
	t_file			*outfile;
	t_input_type	input_type;
	t_output_type	output_type;
	t_heredoc		*heredocs;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_stack
{
	void	*value;
	struct	s_stack *next;
} t_stack;

// ---- FUNCTIONS ----

// -- stacks
t_stack *init_stack();
void push(t_stack **stack, void *value);
void *pop(t_stack **stack);
void *top(t_stack *stack);
void clean(t_stack **stack);
int is_empty(t_stack *stack);
void print_cmd(t_cmd *cmd);
int check_cmds(t_cmd *cmd);
t_cmd	*tokens_to_cmds(t_token *tokens);
void		expand_cmds(t_cmd *tokens);
void		remove_quotes(t_cmd *cmds);

#endif
