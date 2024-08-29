
#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
int	arr_len(char **arr);
char **copy_env(char **envp);
char **delete_env_line(char **copy, char *str);
char **replace_or_create_env_line(char **copy, char *str);
#endif
