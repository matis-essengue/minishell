/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/09/08 13:11:36 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

int	found(char *var, char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i])
	{
		if (env_var[i] == '=')
		{
			if (var[i] == '\0')
				return (1);
			else
				return (0);
		}
		if (env_var[i] != var[i])
			return (0);
		i++;
	}
	return (0);
}

char	*ft_getenvx(char *var, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		if (found(var, env[i]))
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			return (ft_strndup(env[i] + j + 1, ft_strlen(env[i]) - j - 1));
		}
		i++;
	}
	return (NULL);
}

static char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
		&& str[i] != '"' && str[i] != '$' && str[i] != '\'')
		i++;
	var_name = ft_strndup(str, i);
	return (var_name);
}

static char	*handle_special_vars(char *str, t_env *env, int *consumed)
{
	char	*exit_code_str;

	*consumed = 1;
	if (!str[1] || str[1] == ' ' || str[1] == '\t' || str[1] == '\n')
		return (ft_strdup("$"));
	if (str[1] == '?')
	{
		*consumed = 2;
		exit_code_str = ft_itoa(env->exit_status);
		return (exit_code_str);
	}
	if (str[1] == '$')
	{
		*consumed = 2;
		return (ft_strdup("$$"));
	}
	return (NULL);
}

static char	*expand_variable(char *str, t_env *env, int *consumed)
{
	char	*var_name;
	char	*value;
	char	*special_result;

	special_result = handle_special_vars(str, env, consumed);
	if (special_result)
		return (special_result);
	var_name = get_var_name(str + 1);
	*consumed = ft_strlen(var_name) + 1;
	value = ft_getenvx(var_name, env->env);
	free(var_name);
	if (value)
		return (value);
	return (ft_strdup(""));
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

typedef struct s_expand_state
{
	char	*result;
	int		i;
	int		start;
	int		squoted;
	int		dquoted;
}	t_expand_state;

static void	init_expand_state(t_expand_state *state)
{
	state->result = ft_strdup("");
	state->i = 0;
	state->start = 0;
	state->squoted = 0;
	state->dquoted = 0;
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

	init_expand_state(&state);
	while ((*line)[state.i])
	{
		process_char(line, env, &state);
	}
	finalize_expansion(line, &state);
}
