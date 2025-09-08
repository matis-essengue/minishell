/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:04:58 by messengu          #+#    #+#             */
/*   Updated: 2025/09/08 11:53:06 by matis            ###   ########.fr       */
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

static void	expand_variable(
		char **temp, char **start, char **expanded, t_env *env)
{
	char	*var;
	char	*env_var;
	char	*dup;

	if (ft_strcmp(*temp + 1, "\0") == 0 || ft_strcmp(*temp + 1, " ") == 0)
	{
		printf("expand_variable: no variable found\n");
		(*temp)++;
		return ;
	}
	if (*(*temp + 1) && *(*temp + 1) == '$')
		(*temp)++;
	if (*(*temp + 1) && *(*temp + 1) == '?')
	{
		*expanded = ft_strjoin(*expanded, ft_itoa(env->exit_status));
		(*temp)+=2;
		*start = *temp;
	}
	else
	{
		dup = ft_strndup(*start, *temp - *start);
		*expanded = ft_strjoin(*expanded, dup);
		free(dup);
		*start = *temp;
		(*temp)++;
		while (**temp && **temp != ' ' && **temp != '\t' && **temp != '\n'
			&& **temp != '"' && **temp != '$' && **temp != '\'')
			(*temp)++;
		var = ft_strndup(*start + 1, *temp - *start - 1);
		env_var = ft_getenvx(var, env->env);
		if (env_var)
			*expanded = ft_strjoin(*expanded, env_var);
		*start = *temp;
	}
}

void	expand_word(char *word, t_env *env,
	char **res, int *squoted, int *dquoted)
{
	char	*expanded;
	char	*temp;
	char	*start;
	char	*dup;

	temp = word;
	expanded = ft_strdup("");
	start = word;
	while (*temp)
	{
		if (*temp == '"' && !(*squoted))
			*dquoted = !(*dquoted);
		if (*temp == '\'' && !(*dquoted))
			*squoted = !(*squoted);
		if (*temp == '$' && !(*squoted) && (*temp + 1)
			&& *(temp + 1) != '\0' && *(temp + 1) != ' ')
			expand_variable(&temp, &start, &expanded, env);
		else
			temp++;
	}
	dup = ft_strndup(start, temp - start);
	*res = ft_strjoin(expanded, dup);
	free(expanded);
	free(dup);
	free(word);
}

void	expand_line(char **line, t_env *env)
{
	char	*res;
	int		squoted;
	int		dquoted;

	res = ft_strdup("");
	squoted = 0;
	dquoted = 0;
	expand_word(*line, env, &res, &squoted, &dquoted);
	*line = res;
}
