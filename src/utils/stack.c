/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:51:54 by messengu          #+#    #+#             */
/*   Updated: 2025/05/27 16:59:47 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_stack *init_stack()
{
    return (NULL);
}

void push(t_stack **stack, void *value)
{
    t_stack *new_node;

    new_node = (t_stack *)malloc(sizeof(t_stack));
    if (!new_node)
        return;
    new_node->value = value;
    new_node->next = *stack;
    *stack = new_node;
}

void *top(t_stack *stack)
{
	if (!stack)
		return (NULL);
    return (stack->value);
}

void *pop(t_stack **stack)
{
    t_stack *temp;
    void *value;

    if (!*stack)
        return (NULL);
    temp = *stack;
    value = temp->value;
    *stack = (*stack)->next;
    free(temp);
    return (value);
}

void clean(t_stack **stack)
{
    t_stack *current;
    t_stack *next;

    current = *stack;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *stack = NULL;
}

int is_empty(t_stack *stack)
{
    return (stack == NULL);
}
