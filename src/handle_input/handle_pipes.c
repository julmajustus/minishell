/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:58:30 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 20:18:26 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	parse_piped_cmd(t_shell *shell)
{
	clean_redir_allocations(shell);
	init_redir(shell);
	validate_redirections(shell);
	check_forbidden_builtin_in_pipe(shell->parsed_cmd, &shell->exit_code);
}

static void	handle_pipe_exec(t_shell *shell, int i, int *in_fd)
{
	if (shell->last_cmd_in_pipe)
		shell->fd[1] = STDOUT_FILENO;
	execute_command(shell, *in_fd, shell->fd[1]);
	shell->pids[i] = shell->pid;
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (!shell->last_cmd_in_pipe)
		*in_fd = shell->fd[0];
//	free_arr(shell->parsed_cmd);
}

static void	exit_pipes(t_shell *shell, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		shell->retval = check_status(shell->pids[j]);
	free(shell->pids);
	shell->pids = NULL;
	free_arr_and_null(&shell->arr_input);
	shell->in_pipe = 0;
}

void	handle_pipes(t_shell *shell)
{
	int		i;
	int		in_fd;

	in_fd = STDIN_FILENO;
	shell->pids = malloc(arr_len(shell->arr_input) * sizeof(pid_t));
	i = -1;
	while (++i < arr_len(shell->arr_input))
	{
		shell->parsed_cmd = parse_arguments(shell, shell->arr_input[i]);
		parse_piped_cmd(shell);
		if (i < arr_len(shell->arr_input) - 1)
		{
			if (pipe(shell->fd) == -1)
				err("pipe");
		}
		else
			shell->last_cmd_in_pipe = 1;
		handle_pipe_exec(shell, i, &in_fd);
	}
	exit_pipes(shell, i);
}
