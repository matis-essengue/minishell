#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
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

typedef struct s_cmd t_cmd;

char		**get_path(char **envp);
void		free_array(char **split);
void		pipe_function(t_cmd *cmd, char **envp);
void		manage_infile(t_cmd *cmd, int *pipefd);
void		manage_outfile(t_cmd *cmd, int *pipefd);
bool		exe_my_cmd(char *cmd, char **envp);
void		error(char *str, int code);
void		f_error(char *str, int code);
void		manage_here_doc(t_cmd *cmd);

#endif