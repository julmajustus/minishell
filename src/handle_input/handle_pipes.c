/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:58:30 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/27 11:48:12 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_arr_and_null(&shell->parsed_cmd);
}

static void	exit_pipes(t_shell *shell, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		shell->retval = check_status(shell->pids[j]);
	free_and_null((void *)&shell->pids);
	if (shell->piped_cmds)
		free_arr_and_null(&shell->piped_cmds);
	shell->in_pipe = 0;
	free(shell->prompt);
}

void	handle_pipes(t_shell *shell)
{
	int		i;
	int		in_fd;

	in_fd = STDIN_FILENO;
	shell->pids = malloc(arr_len(shell->piped_cmds) * sizeof(pid_t));
	i = -1;
	while (++i < arr_len(shell->piped_cmds))
	{
		shell->parsed_cmd = parse_arguments(shell, shell->piped_cmds[i]);
		parse_piped_cmd(shell);
		if (i < arr_len(shell->piped_cmds) - 1)
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
