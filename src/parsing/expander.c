/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/09/08 13:14:43 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"


static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static void	handle_dollar_sign(char **line, t_env *env, t_expand_state *s)
{
	char	*temp;
	char	*expanded;
	int		consumed;

	if (s->i > s->start)
	{
		temp = ft_strndup(*line + s->start, s->i - s->start);
		s->result = join_and_free(s->result, temp);
	}
	expanded = expand_variable(*line + s->i, env, &consumed);
	s->result = join_and_free(s->result, expanded);
	s->i += consumed;
	s->start = s->i;
}

static void	process_char(char **line, t_env *env, t_expand_state *state)
{
	if ((*line)[state->i] == '\'' && !state->dquoted)
		state->squoted = !state->squoted;
	else if ((*line)[state->i] == '"' && !state->squoted)
		state->dquoted = !state->dquoted;
	else if ((*line)[state->i] == '$' && !state->squoted)
	{
		handle_dollar_sign(line, env, state);
		return ;
	}
	state->i++;
}

static void	finalize_expansion(char **line, t_expand_state *state)
{
	char	*temp;

	if (state->i > state->start)
	{
		temp = ft_strndup(*line + state->start, state->i - state->start);
		state->result = join_and_free(state->result, temp);
	}
	free(*line);
	*line = state->result;
}

void	expand_line(char **line, t_env *env)
{
	t_expand_state	state;

	state.result = ft_strdup("");
	state.i = 0;
	state.start = 0;
	state.squoted = 0;
	state.dquoted = 0;
	while ((*line)[state.i])
	{
		process_char(line, env, &state);
	}
	finalize_expansion(line, &state);
}
