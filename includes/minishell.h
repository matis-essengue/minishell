/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:19:43 by messengu          #+#    #+#             */
/*   Updated: 2025/06/16 12:48:28 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../includes/parsing.h"
#include "../includes/exec.h"

// ---- STRUCTS ENUM ----

typedef enum input_type
{
    STDIN = 0,
    PIPEIN = 0,
    HERE_DOC,
} t_input_type;

typedef enum output_type
{
    STDOUT = 1,
    PIPEOUT = 1,
	
} t_output_type;

// ---- STRUCTS ----

typedef struct s_heredoc
{
	char				*delimiter;
	bool					expand_vars; // parcing here_doc
	struct s_heredoc	*next;
} t_heredoc;

typedef struct s_file
{
	char			*name;
	char			permission[3];
	bool			append; // pour ajouter true or false type
	struct s_file	*next;
} t_file;

typedef struct s_cmd
{
	char			*name;
	char			**args; // les options flag d'une commande
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

// EXEMPLE : cat -e file1 >> file2 file3 | ls -l

// PARSED COMMANDS
// cmd 1:
// [NAME]: cat
// [ARGS]: -e file1 file3
// [INFILE]: NULL
// [OUTFILE]:  >> file2
// [HEREDOC]: NULL
// [OUTPUT_TYPE]: PIPEOUT
// [INPUT_TYPE]: STDIN

// cmd 2:
// [NAME]: ls
// [ARGS]: -l
// [INFILE]: NULL
// [OUTFILE]: NULL
// [HEREDOC]: NULL
// [OUTPUT_TYPE]: STDOUT
// [INPUT_TYPE]: PIPEIN

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
