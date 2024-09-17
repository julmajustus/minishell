/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 05:05:49 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/17 13:50:27 by jmakkone         ###   ########.fr       */
/*   Updated: 2024/09/16 14:26:45 by mpellegr         ###   ########.fr       */
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
	char	*here_doc_eof;
	int		append_mode;
	int		here_doc;
}	t_redir;

typedef struct s_cmd_stack
{
    char				*cmd;
    struct s_cmd_stack	*next;
}	t_cmd_stack;

typedef struct s_shell
{
	char		**envp;
	char		*input;
	char		**chained_cmds;
	char		**tmp_chained_cmds;
	t_cmd_stack *cmd_stack;
	char		**arr_input;
	char		**parsed_cmd;
	char		*path;
	int			pipe_count;
	int			chain_count;
	int			in_pipe;
	int			is_chained_cmd;
	int			preserving_chained_cmds;
	int			execute_next;
	int			is_builtin;
	int			fd[2];
	pid_t		pid;
	int			status;
	int			retval;
	t_redir 	*redir;
	int			exit_code;
	int			builtin_exit_code;
	char		*tilde;
	int			builtin_already_executed;
}	t_shell;

char	**copy_env(char **envp);
char	**delete_env_line(char **copy, char *str);
char	**replace_or_create_env_line(char **copy, char *str);

void	init_shell_variables(t_shell *shell);
void	shell_loop(t_shell *shell);
void	prompt(t_shell *shell);
void	handle_input(t_shell *shell);
int		check_status(pid_t pid);


int		check_if_chained_cmds(t_shell *shell);
void	parse_chained_cmds(t_shell *shell);
void	handle_chained_cmds(t_shell *shell);
void	handle_subcommand(t_shell *shell, int *i);
void	push_to_stack(t_cmd_stack **stack, char *cmd);
void	pop_from_stack(t_shell *shell, t_cmd_stack **stack, char **cmd);
int		stack_len(t_cmd_stack **stack);
void	check_execute_next(t_shell *shell, int i);
void	clean_chained_cmds(t_shell *shell);

void	handle_single_cmd(t_shell *shell);
int		check_if_pipes(t_shell *shell);
void	parse_pipes(t_shell *shell);
void	handle_pipes(t_shell *shell);

void	execute_command(t_shell *shell, int in_fd, int out_fd);
int		check_if_builtin(t_shell *shell);
void	handle_builtin(t_shell *shell, int parent, int child);
char	**exec_builtin(t_shell *shell, int parent, int child);

int		check_if_wildcards(t_shell *shell);
int		match_pattern(const char *pattern, const char *str);
void	handle_wildcards(t_shell *shell);

void	validate_redirections(t_shell *shell);
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
char	**ft_export(char **envp, char *str, int *exit_code);
void	ft_echo(char **cmd);
void	ft_pwd(char **envp);
char	**ft_cd(char **envp, char *path, int *exit_code, int *already_executed, char **cmd_arr);

void	handle_dollar_sign(t_shell shell, char ***args);
void	hande_tilde(char ***args, t_shell shell, int *exit_code);

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
void	exit_syntax_error(t_shell *shell, char *syntax);

int	arr_len(char **arr);
void	init_arr(char **arr, int arr_len);
int	is_empty_str(char *str);
void	free_arr(char **arr);
void	free_arr_and_null(char ***arr);
void	free_cmd_stack(t_cmd_stack **stack);
void	free_shell_allocations(t_shell *shell);

void	init_signals();
void    init_child_signals();
void    handle_ctrl_c(int sig);

#endif
