/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:53:14 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 10:14:12 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

int	check_control_op(t_token *next, t_token *prev)
{
	if (!prev)
		return (0);
	if (!next)
		return (0);
	if (prev->type != TOKEN_WORD)
		return (0);
	if (next->type == TOKEN_CONTROL_OP)
		return (0);
	return (1);
}

int	check_redirect_op(t_token *next)
{
	if (!next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (next->type != TOKEN_WORD)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", next->value);
		return (0);
	}
	return (1);
}

int	check_tokens(t_token *tokens)
{
	t_token	*prev;
	t_token	*current;

	prev = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_CONTROL_OP)
		{
			if (!check_control_op(current->next, prev))
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		else if (current->type == TOKEN_REDIRECT_OP)
		{
			if (!check_redirect_op(current->next))
				return (0);
		}
		prev = current;
		current = current->next;
	}
	printf("tokens are valid\n");
	return (1);
}
