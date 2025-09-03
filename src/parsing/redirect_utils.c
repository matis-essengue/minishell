/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:14:38 by matis             #+#    #+#             */
/*   Updated: 2025/09/03 11:23:48 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

void	handle_output_redirect(t_cmd *cmd,
	t_token *current, t_file **start_outfile)
{
	if (cmd->outfile == NULL)
	{
		cmd->outfile = malloc(sizeof(t_file));
		*start_outfile = cmd->outfile;
	}
	else
	{
		cmd->outfile->next = malloc(sizeof(t_file));
		cmd->outfile = cmd->outfile->next;
	}
	cmd->outfile->name = ft_strdup(current->next->value);
	cmd->outfile->permission[0] = '2';
	cmd->outfile->permission[1] = '2';
	cmd->outfile->permission[2] = '2';
	cmd->outfile->append = (ft_strncmp(current->value, ">>", 2) == 0);
	cmd->outfile->fd = -1;
	cmd->outfile->next = NULL;
}

void	handle_input_redirect(t_cmd *cmd,
	t_token *current, t_file **start_infile)
{
	if (cmd->infile == NULL)
	{
		cmd->infile = malloc(sizeof(t_file));
		*start_infile = cmd->infile;
	}
	else
	{
		cmd->infile->next = malloc(sizeof(t_file));
		cmd->infile = cmd->infile->next;
	}
	cmd->infile->name = ft_strdup(current->next->value);
	cmd->infile->permission[0] = '4';
	cmd->infile->permission[1] = '4';
	cmd->infile->permission[2] = '4';
	cmd->infile->append = 0;
	cmd->infile->fd = -1;
	cmd->infile->next = NULL;
}
