/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:01:04 by messengu          #+#    #+#             */
/*   Updated: 2025/05/28 18:39:23 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

/**
 * @brief Get the variable name from a command
 *
 * @param cmd The command
 * @return The variable name
 */
char	*get_var_name(char *cmd)
{
	int		i;
	char	*var_name;

	i = 0;
	while (cmd[i] != '=')
		i++;
	var_name = ft_strndup(cmd, i);
	return (var_name);
}

/**
 * @brief Check if a variable name is valid
 *
 * @param var_name The variable name
 * @return 1 if the variable name is valid, 0 otherwise
 */
int	is_valid_var_name(char *var_name)
{
	int	i;

	if (!var_name)
		return (0);
	if (!ft_isalpha(var_name[0]))
		return (0);
	i = 1;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Check if an export command is valid
 *
 * @param cmd The command
 * @return 1 if the export command is valid, 0 otherwise
 */
int	is_valid_export(t_cmd *cmd)
{
	int		i;
	char	*var_name;

	if (cmd->args != NULL)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			var_name = get_var_name(cmd->args[i]);
			if (!is_valid_var_name(var_name))
			{
				printf(
					"minishell: export: `%s': not a valid identifier\n",
					var_name);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

/**
 * @brief Check if the commands are valid
 *
 * @param cmd The command
 * @return 1 if the commands are valid, 0 otherwise
 */
int	check_cmds(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (ft_strncmp(current->name, "export", 6) == 0
			&& ft_strlen(current->name) == 6)
		{
			if (!is_valid_export(current))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
