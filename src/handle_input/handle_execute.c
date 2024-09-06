/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:37:46 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 12:03:10 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prerun_builtin(t_shell *shell)
{
	int	saved_stdout;
	int	saved_stderr;
	int	dev_null_fd;

	if (check_if_builtin(shell->parsed_cmd))
	{
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
	if (check_if_builtin(shell->parsed_cmd))
	{
		handle_builtin(shell);
		free_shell_allocations(shell);
		return (0);
	}
	shell->parsed_cmd = cmd_validator(shell->parsed_cmd);
	shell->path = get_path(shell);
	retval = execve(shell->path, shell->parsed_cmd, shell->envp);
	free_shell_allocations(shell);
	free(shell->path);
	if (retval == -1)
		exit (1);
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
	pid_t pid;

	shell->redir = init_redir();
	parse_redirections(shell);
	handle_redirections(shell->redir);
	prerun_builtin(shell);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		err("fork");
	if (pid == 0)
	{
		handle_fds(in_fd, out_fd);
		exec_child(shell);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		shell->retval = check_status(pid);
		signal(SIGINT, handle_ctrl_c);
	}
	free(shell->redir);
}
