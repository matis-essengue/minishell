/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:19:43 by armosnie          #+#    #+#             */
/*   Updated: 2025/09/09 11:49:46 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/minishell.h"

char	*return_oldpwd(char **env)
{
	char	*pwd;
	char	*new_oldpwd;

	pwd = ft_getenv("PWD=", env);
	if (!pwd)
		return (NULL);
	new_oldpwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	if (!new_oldpwd)
		return (NULL);
	return (new_oldpwd);
}

char	*return_pwd(void)
{
	char	*pwd;
	char	*result;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	result = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!result)
		return (NULL);
	return (result);
}

int	change_update_pwd_and_env(char ***env)
{
	char	*new_oldpwd;
	char	*new_pwd;

	new_oldpwd = return_oldpwd(*env);
	printf("new_old pwd : %s\n", new_oldpwd);
	if (!new_oldpwd)
		return (1);
	if (get_my_export_env(env, new_oldpwd) != 0)
		return (free(new_oldpwd), 1);
	free(new_oldpwd);
	new_pwd = return_pwd();
	printf("new pwd : %s\n", new_pwd);
	if (!new_pwd)
		return (1);
	if (get_my_export_env(env, new_pwd) != 0)
		return (1);
	free(new_pwd);
	return (0);
}

int	handle_cd_errors(t_cmd *cmd)
{
	if (!cmd->args)
		return (printf("minishell: cd: absolute or relative path only allowed\n"),
			1);
	if (cmd->args[0] && cmd->args[1])
		return (printf("minishell: cd: too many arguments\n"), 1);
	if (cmd->args[0][0] == '-' && cmd->args[0][1])
		return (printf("minishell: cd: '-': There is no option allowed\n"), 2);
	if ((cmd->args && cmd->args[0][0] == '~' && !cmd->args[0][1]) || (cmd->args
			&& cmd->args[0][0] == '-' && !cmd->args[0][1]))
		return (printf("minishell: cd: absolute or relative path only allowed\n"),
			1);
	return (0);
}

int	built_in_cd(t_cmd *cmd, t_env *env)
{
	DIR	*dir;
	int	ret;

	if (handle_cd_errors(cmd) == 1)
		return (1);
	dir = opendir(cmd->args[0]);
	if (dir == NULL)
	{
		printf("");
		return (perror("cd: dir"), 1);
	}
	if (chdir(cmd->args[0]) == -1)
	{
		perror("");
		return (closedir(dir), 1);
	}
	ret = change_update_pwd_and_env(&env->env);
	if (closedir(dir) == -1)
	{
		printf("minishell: cd: closedir: error closing directory stream");
		return (perror(""), 1);
	}
	return (ret);
}
