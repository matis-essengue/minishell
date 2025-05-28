/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:32:15 by messengu          #+#    #+#             */
/*   Updated: 2025/05/27 11:19:59 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *token)
{
	t_token *temp;

	temp = *tokens;
	if (temp)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = token;
	}
	else
		*tokens = token;
}

const char	*get_token_type_str(int type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_REDIRECT_OP)
		return ("REDIRECT");
	if (type == TOKEN_CONTROL_OP)
		return ("CONTROL");
	return ("UNKNOWN");
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		free(current->value);
		current = current->next;
	}
	free(tokens);
}
