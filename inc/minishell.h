
#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <sys/wait.h>

char **copy_env(char **envp);
char **delete_env_line(char **copy, char *str);
char **replace_or_create_env_line(char **copy, char *str);

void prompt(char **copy_envp);

int	arr_len(char **arr);
char	*create_path(char **cmd, char **envp);
char	**parse_input(char *cmd);
void	free_arr(char **arr);
void	error_no_file(char *file);
void	error_no_permission(char *str);
void	error_command_not_found(char *cmd);
void	error_is_a_directory(char *str);

#endif
