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
# include <termios.h>

# define FD_STDIN 0
# define FD_STDOUT 1
# define READ 0
# define WRITE 1

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

// struct t_env

t_env					*init_env(char **envp);
char					**copy_env(char **envp);
void					free_my_env(t_env *my_env);

// built-in utils

long long				ft_atoll(char *str);
int						check_long(char *str);
int						is_valid_number(char *str);
int						invalid_option(char **args, char *str);
int						env_len(char **envp);
int						check_is_same_var(char *s1, char *s2);
char					*find_var(char *target_var, char **env);
char					**copy_and_replace_my_env(char **env, char *var);

// built-in : export unset utils

char					*ft_getenv(char *var, char **env);
int						get_my_export_env(char ***env, char *new_var);
char					**copy_and_add_my_env(char **env, char *var);
char					**copy_and_replace_my_env(char **env, char *var);

int						get_my_unset_env(char ***env, char *new_var);

// built-in

int						child_process_built_in(t_cmd *cmd, t_env *env);
int						parent_process_built_in(t_cmd *cmd, t_env *env);
bool					is_built_in(t_cmd *cmd);
int						built_in_echo(t_cmd *cmd);
int						built_in_cd(t_cmd *cmd, t_env *env);
int						built_in_pwd(t_cmd *cmd);
int						built_in_export(t_cmd *cmd, t_env *env, int code_error);
int						built_in_unset(t_cmd *cmd, t_env *env);
int						built_in_env(t_cmd *cmd, t_env *env);
int						built_in_exit(t_cmd *cmd, int status);

// errors

void					free_array(char **split);
void					error(t_cmd *cmd, char *str, int code);
void					free_all_struct(t_cmd *cmd);
void					close_all_fd(int *fd);

// parent process

int						execute_command(t_cmd *cmd, t_env *env);
int						pipe_function(t_cmd *cmd, pid_t *pid, int exit_status,
							t_env *env);
int						parent_call(t_cmd *cmd, int prev_read_fd);
void					pipe_check_or_create(t_cmd *cmd, int prev_read_fd);
void					pidarray_check(t_cmd *cmd, pid_t *pid, int prev_read_fd,
							int i);

// child process

void					child_call(t_cmd *cmd, t_cmd *cmd_list, t_env *env,
							int prev_read_fd);
void					files_and_management(t_cmd *cmd, t_cmd *cmd_list,
							int prev_read_fd);
void					unused_heredoc_fd(t_cmd *current, t_cmd *cmd_list);
int						wait_child(pid_t *pid, int size);

// manage_files

void					open_infile(t_cmd *cmd);
void					open_outfile(t_cmd *cmd);
void					manage_heredocs(t_cmd *cmd, t_env *env);

// get_path

char					**get_path(char **envp);
bool					exe_my_cmd(t_cmd *cmd, t_env *env);


// utils

int						count_cmd(t_cmd *cmd);
int						count_args(t_cmd *cmd);
int						count_all_cmd_args(t_cmd *cmd);
void					print_array(char **array);

// term state

int						save_termios(struct termios *out_saved);
void 					restore_termios(const struct termios *saved);

#endif
