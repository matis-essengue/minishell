/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:32:15 by messengu          #+#    #+#             */
/*   Updated: 2025/09/04 12:06:24 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/**
 * @brief Create a token
 *
 * @param value The value of the token
 * @param type The type of the token
 * @return The created token
 */
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

/**
 * @brief Add a token to the end of the list
 *
 * @param tokens The list of tokens
 * @param token The token to add
 */
void	add_token(t_token **tokens, t_token *token)
{
	t_token	*temp;

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

/**
 * @brief [DEBUG FUNCTION] Get the string
 * representation of a token type
 *
 * @param type The type of the token
 * @return The string representation of the token type
 */
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

/**
 * @brief Free the tokens list
 *
 * @param tokens The list of tokens to free
 */
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*temp;

	current = tokens;
	while (current != NULL)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
}
