/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:19:43 by messengu          #+#    #+#             */
/*   Updated: 2025/05/20 14:56:35 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>

// ---- STRUCTS ----

typedef enum input_type
{
    STDIN,
    PIPE,
    HERE_DOC,
    INFILE,
} t_input_type;

typedef enum output_type
{
    STDOUT,
    PIPE,
    OUTFILE,
} t_output_type;

typedef struct s_cmd
{
    char    *name;
    char    **args;
    t_input_type input_type;
    t_output_type output_type;
} t_cmd;

typedef struct s_stack
{
    t_cmd *cmd;
    struct s_stack *next;
} t_stack;

// ---- FUNCTIONS ----

// -- stacks
t_stack *init_stack();
void push(t_stack **stack, t_cmd *cmd);
t_cmd *pop(t_stack **stack);
void clean(t_stack **stack);
int is_empty(t_stack *stack);

#endif
