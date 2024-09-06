/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 05:05:49 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 19:43:27 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

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

typedef struct s_redir
{
	char	*input_file;
	char	*output_file;
	int	append_mode;
	int	here_doc;
}	t_redir;

typedef struct s_shell
{
	char	**envp;
	char	*input;
	char	**arr_input;
	char	**parsed_cmd;
	char	*path;
	int	pipe_count;
	int	in_pipe;
	int	fd[2];
	pid_t	pid;
	int	status;
	int	retval;
	t_redir *redir;

}	t_shell;

char	**copy_env(char **envp);
char	**delete_env_line(char **copy, char *str);
char	**replace_or_create_env_line(char **copy, char *str);

void	init_shell_variables(t_shell *shell);
void	shell_loop(t_shell *shell);
void	prompt(t_shell *shell);
void	handle_input(t_shell *shell);

int	check_if_pipes(t_shell *shell);
void	parse_pipes(t_shell *shell);
void	handle_pipes(t_shell *shell);
void	execute_command(t_shell *shell, int in_fd, int out_fd);
int	check_if_builtin(t_shell *shell);
void	handle_builtin(t_shell *shell);
char	**exec_builtin(t_shell *shell);

void	parse_redirections(t_shell *shell);
void	handle_redirections(t_redir *redir);

void	validate_cmd(t_shell *shell);
char	*validate_path(t_shell *shell);
char	**parse_arguments(t_shell *shell, char *input);
char	**add_arg(char **args, char *arg, size_t *argc, size_t *arg_size);
char	*append_char(char *str, char c);

void	ft_exit(t_shell *shell);
char	**ft_env(char **envp);
char	**ft_unset(char **envp, char *str);
char	**ft_export(char **envp, char *str);
void	ft_echo(char **cmd);
void	ft_pwd(char **envp);
char	**ft_cd(char **envp, char *path);

void	check_if_env_var(char **envp, char ***args);

void	err(const char *msg);
void	err_cmd_notfound(char *cmd);
void	err_nofile(char *file);
void	err_is_directory(char *cmd);
void	err_no_permission(char *cmd);
void	err_syntax(char *cmd);
void	exit_cmd_notfound(t_shell *shell);
void	exit_is_directory(t_shell *shell);
void	exit_no_permission(t_shell *shell);
void	exit_no_file(t_shell *shell);
void	exit_syntax_error(t_shell *shell);

int	arr_len(char **arr);
void	init_arr(char **arr, int arr_len);
int	is_empty_str(char *str);
void	free_arr(char **arr);
void	free_shell_allocations(t_shell *shell);

void	init_signals();
void    init_child_signals();
void    handle_ctrl_c(int sig);

#endif
