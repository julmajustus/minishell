/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 05:05:49 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 13:14:12 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

# define ARG_ARR_SIZE 256

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
	int		dollar_sign;
}	t_parse_state;

typedef struct s_redir
{
	char	**input_file;
	char	**output_file;
	char	**here_doc_eof;
	int		input_file_count;
	int		output_file_count;
	int		here_doc_count;
	int		append_mode;
	int		here_doc;
	int		*valid_tokens;
	int		token_count;
	int		token_counter;
	int		output_file_first;
	int		syntax_err;
}	t_redir;

typedef struct s_cmd_stack
{
	char				*cmd;
	struct s_cmd_stack	*next;
}	t_cmd_stack;

typedef struct s_shell
{
	char		**envp;
	char		**pending_exports;
	int			pending_exports_size;
	char		*input;
	char		**chained_cmds;
	char		**tmp_chained_cmds;
	t_cmd_stack	*cmd_stack;
	char		**piped_cmds;
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
	pid_t		*pids;
	int			status;
	int			retval;
	t_redir		*redir;
	int			exit_code;
	char		*tilde;
	int			builtin_already_executed;
	int			last_cmd_in_pipe;
	char		*prompt;
}	t_shell;

char	**copy_env(char **envp);
char	**delete_env_line(char **copy, char *str);
char	**replace_or_create_env_line(char **copy, char *str);
void	sort_envp_alphabetically(char **envp);
void	sort_pending_exports_alphabetically(char **pending_exports);
void	print_sorted_exports(char **envp, char **pending_exports);

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
void	pop_from_stack(t_cmd_stack **stack, char **cmd);
int		stack_len(t_cmd_stack **stack);
void	check_execute_next(t_shell *shell, int i);
void	clean_chained_cmds(t_shell *shell);

void	handle_single_cmd(t_shell *shell);
int		check_if_pipes(t_shell *shell);
void	parse_piped_cmds(t_shell *shell);
void	handle_pipes(t_shell *shell);

void	execute_command(t_shell *shell, int in_fd, int out_fd);
int		check_if_builtin(t_shell *shell);
void	handle_builtin(t_shell *shell, int parent, int child);
char	**exec_builtin(t_shell *shell, int parent, int child);
void	check_forbidden_builtin_in_pipe(char **cmd_arr, int *exit_code);

void	check_if_wildcards(t_shell *shell);
int		match_pattern(const char *pattern, const char *str);
void	handle_wildcards(t_shell *shell);

void	init_redir(t_shell *shell);
void	validate_redirections(t_shell *shell);
void	parse_redirections(t_shell *shell);
int		check_if_redir_token(t_shell *shell, char *cmd, char \
		**new_parsed_cmd, int *j);
void	handle_redirections(t_shell *shell);
void	handle_here_doc(t_shell *shell);
void	validate_input_redir(t_shell *shell, char **parsed_cmd, \
		char *cmd, int *j);
void	validate_output_redir(t_shell *shell, char **parsed_cmd, \
		char *cmd, int *j);

void	validate_cmd(t_shell *shell);
char	*validate_path(t_shell *shell);
char	**parse_arguments(t_shell *shell, char *input);
char	**add_arg(char **args, char *arg, size_t *argc, size_t *arg_size);
char	*append_char(char *str, char c);

void	ft_exit(t_shell *shell);
char	**ft_env(char **envp, char **parsed_cmd, int *exit_code);
char	**ft_unset(char **envp, char *str);
char	**ft_export(t_shell *shell, char *str);
void	ft_echo(char **cmd);
void	ft_pwd(char **envp);
char	**ft_cd(t_shell *shell, char *path);

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

int		arr_len(char **arr);
void	append_array(char *content, char ***new_arr, int *new_arr_size);
void	init_arr(char **arr, int arr_len);
int		is_empty_str(char *str);
void	free_arr(char **arr);
void	free_and_null(void **ptr);
void	free_arr_and_null(char ***arr);
void	free_cmd_stack(t_cmd_stack **stack);
void	free_shell_allocations(t_shell *shell);
void	clean_redir_allocations(t_shell *shell);
int		update_quote_state(char c, int *single_quote, int *double_quote);

void	init_signals(void);
void	init_child_signals(void);
void	handle_ctrl_c(int sig);

char	**err_oldpwd_not_set(char **envp, char *new_old_pwd, int **exit_code);
int		find_new_len(char *path, char *new_old_pwd);
char	**err_too_many_args(char **envp, int *exit_code);

void	add_space(char **input_var);
void	replace_env_var(char **envp, char **temp_var, int *match_found);
void	remove_empty_args(char ***args);

#endif
