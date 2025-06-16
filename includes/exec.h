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

// typedef struct s_data
// {
// 	char	*outfile;
// 	char	*infile;
// 	int		n_cmd;
// 	char	**cmd;
// 	char	**envp;
// 	bool	here_doc;
// 	char	*limiter;

// }			t_data;

char		**get_path(char **envp);
void		free_array(char **split);
void		pipe_function(t_cmd *cmd);
void		manage_infile(t_cmd *cmd, int *pipefd);
void		manage_outfile(t_cmd *cmd, int *pipefd);
bool		exe_my_cmd(char *cmd, char **envp);
void		error(char *str, int code);
void		f_error(char *str, int code);
void		manage_here_doc(t_cmd *cmd);

#endif