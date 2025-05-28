/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:19:43 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 11:44:01 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../includes/parsing.h"

// ---- STRUCTS ----

typedef enum input_type
{
    STDIN,
    PIPEIN,
    HERE_DOC,
    INFILE,
} t_input_type;

typedef enum output_type
{
    STDOUT,
    PIPEOUT,
    OUTFILE,
} t_output_type;

typedef struct s_cmd
{
    char    *name;
    char    **args;
	char	*infile;
	char	*outfile;
    t_input_type input_type;
    t_output_type output_type;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_stack
{
    void *value;
    struct s_stack *next;
} t_stack;

// ---- FUNCTIONS ----

// -- stacks
t_stack *init_stack();
void push(t_stack **stack, void *value);
void *pop(t_stack **stack);
void *top(t_stack *stack);
void clean(t_stack **stack);
int is_empty(t_stack *stack);

#endif
