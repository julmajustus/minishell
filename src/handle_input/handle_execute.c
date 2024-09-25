/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:37:46 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/25 18:31:56 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    handle_fds(t_shell *shell, int in_fd, int out_fd)
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

static void	exec_child(t_shell *shell)
{
	init_child_signals();
	if (check_if_builtin(shell))
	{
		handle_builtin(shell, 0, 1);
		free_shell_allocations(shell);
		if (!shell->builtin_exit_code)
			exit (EXIT_SUCCESS);
		else
			exit (shell->builtin_exit_code);
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
		exit (EXIT_SUCCESS);
	}
}

int check_status(pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
    {
		if (WTERMSIG(status) == SIGQUIT)
			write (2, "Quit (core dumped)\n", 19);
		if (WTERMSIG(status) == SIGINT)
			write (2, "\n", 1);
		return 128 + WTERMSIG(status);
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return -1;
}

void execute_command(t_shell *shell, int in_fd, int out_fd)
{
    handle_builtin(shell, 1, 0);
    signal(SIGINT, SIG_IGN);
    shell->pid = fork();
    if (shell->pid == -1)
        err("fork");
    if (shell->pid == 0)
    {
        if (shell->exit_code == 1)
            exit (EXIT_FAILURE);
		if (shell->in_pipe)
			handle_here_doc(shell);
        handle_fds(shell, in_fd, out_fd);
		handle_redirections(shell, &shell->exit_code);
		if (shell->exit_code != 0)
			exit (shell->exit_code);
        exec_child(shell);
        if (shell->builtin_exit_code == 0)
            exit (EXIT_SUCCESS);
        exit(EXIT_FAILURE);
    }
    else
    {
		if (shell->in_pipe && shell->redir->here_doc)
			waitpid(shell->pid, NULL, 0);
        if (!shell->last_cmd_in_pipe && out_fd != STDOUT_FILENO)
            close(out_fd);
        if (!shell->last_cmd_in_pipe && in_fd != STDIN_FILENO)
            close(in_fd);
        signal(SIGINT, handle_ctrl_c);
    }
}
