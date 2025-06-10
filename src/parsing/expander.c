/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/05/29 15:26:43 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

static char	*expand_variable(char **temp, char **start, char *expanded)
{
	if (*(*temp + 1) && *(*temp + 1) == '$')
	{
		(*temp)++;
		return (expanded);
	}
	if (*(*temp + 1) && *(*temp + 1) == '?')
	{
		// TODO: expand $?
		(*temp)++;
		(*temp)++;
		return (expanded);
	}
	expanded = ft_strjoin(expanded, ft_strndup(*start, *temp - *start));
	*start = *temp;
	(*temp)++;
	while (**temp && **temp != ' ' && **temp != '\t' && **temp != '\n' && **temp != '"' && **temp != '$' && **temp != '\'')
		(*temp)++;
	if (getenv(ft_strndup(*start + 1, *temp - *start - 1)) != NULL)
		expanded = ft_strjoin(expanded, getenv(ft_strndup(*start + 1, *temp - *start - 1)));
	*start = *temp;
	return (expanded);
}

char	*expand_word(char *word)
{
	char	*expanded;
	char	*temp;
	char	*start;
	int		squoted;

	temp = word;
	expanded = ft_strdup("");
	squoted = 0;
	start = word;
	while (*temp)
	{
		if (*temp == '\'')
			squoted = !squoted;
		if (*temp == '$' && !squoted)
			expanded = expand_variable(&temp, &start, expanded);
		else
			temp++;
	}
	expanded = ft_strjoin(expanded, ft_strndup(start, temp - start));
	return (expanded);
}

void	expand_cmds(t_cmd *tokens)
{
	t_cmd	*current;
	int		i;

	current = tokens;
	while (current)
	{
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				current->args[i] = expand_word(current->args[i]);
				i++;
			}
		}
		current = current->next;
	}
}
