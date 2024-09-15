/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:37:46 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/15 22:34:34 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prerun_builtin(t_shell *shell)
{
	int	saved_stdout;
	int	saved_stderr;
	int	dev_null_fd;
	
	if (check_if_builtin(shell))
	{
		if (!ft_strcmp(shell->parsed_cmd[0], "echo"))
			return ;
		shell->is_builtin = 1;
		saved_stdout = dup(STDOUT_FILENO);
		saved_stderr = dup(STDERR_FILENO);
		dev_null_fd = open("/dev/null", O_WRONLY);
		if (dev_null_fd == -1)
		{
			perror("open /dev/null");
			exit(EXIT_FAILURE);
		}
		dup2(dev_null_fd, STDOUT_FILENO);
		dup2(dev_null_fd, STDERR_FILENO);
		close(dev_null_fd);
		handle_builtin(shell);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);
		close(saved_stdout);
		close(saved_stderr);
	}
}

static void	handle_fds(int in_fd, int out_fd)
{
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

static	int	exec_child(t_shell *shell)
{
	int		retval;

	init_child_signals();
	if (check_if_builtin(shell))
	{
		handle_builtin(shell);
		free_shell_allocations(shell);
		exit (EXIT_SUCCESS);
	}
	validate_cmd(shell);
	shell->path = validate_path(shell);
	retval = execve(shell->path, shell->parsed_cmd, shell->envp);
	free_shell_allocations(shell);
	if (retval == -1)
		exit (EXIT_FAILURE);
	return (retval);
}

static	int check_status(pid_t pid)
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
	prerun_builtin(shell);
	signal(SIGINT, SIG_IGN);
	shell->pid = fork();
	if (shell->pid == -1)
		err("fork");
	if (shell->pid == 0)
	{
		if (shell->exit_code == 1)
			exit (EXIT_FAILURE);
		validate_redirections(shell);
		handle_redirections(shell->redir);
		handle_fds(in_fd, out_fd);
		exec_child(shell);
		if (shell->builtin_exit_code == 0)
			exit (EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		shell->retval = check_status(shell->pid);
		signal(SIGINT, handle_ctrl_c);
	}
}
