/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:37:46 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 22:01:38 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_fds(t_shell *shell, int in_fd, int out_fd)
{
	if (!shell->last_cmd_in_pipe && shell->in_pipe)
		close(shell->fd[0]);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

static void	handle_exec_builtin(t_shell *shell)
{
	handle_builtin(shell, 0, 1);
	free_shell_allocations(shell);
	if (!shell->exit_code)
	{
		free_shell_allocations(shell);
		exit (EXIT_SUCCESS);
	}
	else
	{
		free_shell_allocations(shell);
		exit (shell->exit_code);
	}
}

static void	exec_child(t_shell *shell)
{
	init_child_signals();
	if (check_if_builtin(shell))
	{
		handle_exec_builtin(shell);
	}
	else
	{
		validate_cmd(shell);
		shell->path = validate_path(shell);
		if (check_if_builtin(shell) == 0)
		{
			if (execve(shell->path, shell->parsed_cmd, shell->envp) == -1)
			{
				free_shell_allocations(shell);
				exit (EXIT_FAILURE);
			}
		}
		free_shell_allocations(shell);
		exit (EXIT_SUCCESS);
	}
}

static void	handle_child_process(t_shell *shell, int in_fd, int out_fd)
{
	if (shell->exit_code != 0)
	{
		free_shell_allocations(shell);
		exit (shell->exit_code);
	}
	if (shell->in_pipe)
		handle_here_doc(shell);
	handle_fds(shell, in_fd, out_fd);
	handle_redirections(shell);
	if (shell->exit_code != 0)
	{
		free_shell_allocations(shell);
		exit (shell->exit_code);
	}
	exec_child(shell);
	if (shell->exit_code == 0)
	{
		free_shell_allocations(shell);
		exit (EXIT_SUCCESS);
	}
	free_shell_allocations(shell);
	exit(EXIT_FAILURE);
}

void	execute_command(t_shell *shell, int in_fd, int out_fd)
{
	if (check_if_builtin(shell))
		handle_builtin(shell, 1, 0);
	signal(SIGINT, SIG_IGN);
	shell->pid = fork();
	if (shell->pid == -1)
		err("fork");
	if (shell->pid == 0)
	{
		handle_child_process(shell, in_fd, out_fd);
	}
	else
	{
		if (shell->in_pipe && shell->redir->here_doc)
			check_status(shell->pid);
		if (!shell->last_cmd_in_pipe && out_fd != STDOUT_FILENO)
			close(out_fd);
		if (!shell->last_cmd_in_pipe && in_fd != STDIN_FILENO)
			close(in_fd);
		signal(SIGINT, handle_ctrl_c);
	}
}
