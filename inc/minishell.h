
#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

# define ARG_ARR_SIZE 8

typedef enum e_state
{
	OUTSIDE,
	INSIDE_SINGLE_QUOTE,
	INSIDE_DOUBLE_QUOTE,
	ESCAPE_SEQUENCE
}	t_state;

typedef struct s_parse_state
{
	char	**args;
	char	*arg;
	size_t	argc;
	size_t	arg_size;
	t_state	state;
}	t_parse_state;

typedef struct s_shell
{
	char	**envp;
	char	*input;
    char	**arr_input;
    char	*path;
    pid_t	pid;
    int		status;

}	t_shell;

char	**copy_env(char **envp);
char	**delete_env_line(char **copy, char *str);
char	**replace_or_create_env_line(char **copy, char *str);

void	shell_loop(t_shell *shell);
void	prompt(t_shell *shell);
void	handle_input(t_shell *shell);


int		check_if_builtin(char **cmd);
char	**exec_builtin(char **cmd, char **envp);
void	ft_exit(char **envp, char **cmd);
char	**ft_env(char **envp);
char	**ft_unset(char **envp, char *str);
char	**ft_export(char **envp, char *str);
void	ft_echo(char **cmd);
void	ft_pwd(char **envp);
char	**ft_cd(char **envp, char *path);

char	*create_path(char **cmd, char **envp);
char	**parse_arguments(t_shell shell);
char	**add_arg(char **args, char *arg, size_t *argc, size_t *arg_size);
char	*append_char(char *str, char c);
void	check_if_env_var(char **envp, char ***args);

int		arr_len(char **arr);
int		is_empty_str(char *str);
void	free_arr(char **arr);
void	error_no_file(char *file);
void	error_no_permission(char *str);
void	error_command_not_found(char *cmd);
void	error_is_a_directory(char *str);

#endif
