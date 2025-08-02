#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define FD_STDIN 0
# define FD_STDOUT 1
# define READ 0
# define WRITE 1

typedef struct s_cmd	t_cmd;

bool					is_built_in(char *cmd);
char					**get_path(char **envp);
void					free_array(char **split);
void					open_infile(t_cmd *cmd, int *pipe_fd);
void					open_outfile(t_cmd *cmd, int *pipe_fd);
void					manage_heredocs(t_cmd *cmd);
void					pipe_function(t_cmd *cmd, char **envp);
void					wait_child(void);
bool					exe_my_cmd(t_cmd *cmd, char **envp);
void					error(t_cmd *cmd, char *str, int code);
void					close_all_fd(int *fd);
int						count_cmd(t_cmd *cmd);
int						count_cmd_args(t_cmd *cmd);
// void					open_heredocs(t_cmd *cmd, int *pipe_fd);
// void					manage_here_doc(t_cmd *cmd);

#endif