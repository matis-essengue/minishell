/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:43:06 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/04 13:47:50 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

char	*join_slash(char *path, char *cmd_cut)
{
	char	*slash;
	char	*full_path;

	slash = ft_strjoin(path, "/");
	if (slash == NULL)
		return (NULL);
	full_path = ft_strjoin(slash, cmd_cut);
	if (full_path == NULL)
		return (NULL);
	free(slash);
	return (full_path);
}

void	exec(char *cmd_cut, char **cmd, char **path, char **envp)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path[i])
	{
		full_path = join_slash(path[i], cmd_cut);
		if (full_path == NULL)
			return ;
		if (access(full_path, F_OK | X_OK) == 0)
			execve(full_path, cmd, envp);
		free(full_path);
		i++;
	}
}

char	**recup_all_args(t_cmd *cmd, char **full_cmd, int i, int j)
{
	while (cmd->args && cmd->args[j])
	{
		full_cmd[i] = ft_strdup(cmd->args[j]);
		if (full_cmd[i] == NULL)
			return (free_array(full_cmd), NULL);
		i++;
		j++;
	}
	full_cmd[i] = NULL;
	return (full_cmd);
}

char	**recup_full_cmd(t_cmd *cmd)
{
	char	**full_cmd;
	int		i;
	int		j;
	int		total_arg;

	i = 0;
	total_arg = count_all_cmd_args(cmd);
	if (total_arg == 0)
		return (NULL);
	full_cmd = malloc(sizeof(char *) * (total_arg + 1));
	if (full_cmd == NULL)
		return (NULL);
	if (cmd->name)
	{
		full_cmd[i] = ft_strdup(cmd->name);
		if (full_cmd[i] == NULL)
			return (free_array(full_cmd), NULL);
		i++;
	}
	j = 0;
	full_cmd = recup_all_args(cmd, full_cmd, i, j);
	if (full_cmd == NULL)
		return (NULL);
	return (full_cmd);
}

bool	exe_my_cmd(t_cmd *cmd, t_env *env)
{
	char	**path;
	char	**full_cmd;

	full_cmd = NULL;
	if (cmd->name)
		full_cmd = recup_full_cmd(cmd);
	if (full_cmd == NULL)
		return (false);
	if (access(full_cmd[0], F_OK | X_OK) == 0)
		execve(full_cmd[0], full_cmd, env->env);
	path = get_path(env->env);
	if (path == NULL)
	{
		free_array(full_cmd);
		free_array(path);
		error(cmd, cmd->name, 127);
	}
	exec(full_cmd[0], full_cmd, path, env->env);
	free_array(path);
	free_array(full_cmd);
	error(cmd, cmd->name, 127);
	return (false);
}
