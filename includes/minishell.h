/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:19:43 by messengu          #+#    #+#             */
/*   Updated: 2025/09/09 15:40:10 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include "../includes/exec.h"
# include "../includes/parsing.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# define MAX_PROCESSES 256 // pour mon tableau de pid

// ---- STRUCTS ----

typedef struct sigaction		t_sa;
extern volatile sig_atomic_t	g_signal;

typedef enum input_type
{
	STDIN,
	PIPEIN,
	HERE_DOC,
}						t_input_type;

typedef enum output_type
{
	STDOUT,
	PIPEOUT,
}						t_output_type;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	int					heredoc_fd;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_file
{
	char				*name;
	char				permission[3];
	int					append;
	int					fd;
	struct s_file		*next;
}						t_file;

typedef struct s_cmd
{
	char				*name;
	char				**args;
	int					pipefd[2];
	int					exit_status;
	pid_t				pid[MAX_PROCESSES];
	t_file				*infile;
	t_file				*outfile;
	t_input_type		input_type;
	t_output_type		output_type;
	t_heredoc			*heredocs;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env
{
	char				**env;
	int					is_cpy;
	int					exit_status;
}						t_env;

// ---- FUNCTIONS ----

t_cmd					*parse(char *line, t_env *env);
int						execute_command(t_cmd *cmd, t_env *env);
void					print_cmd(t_cmd *cmd);
int						check_cmds(t_cmd *cmd);
void					set_signal_action(void);

#endif
