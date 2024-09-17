/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:58:30 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/17 13:57:52 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_pipes(t_shell *shell)
{
	int    i;
	int single_quote;
	int double_quote;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (shell->input[++i])
	{
		if (shell->input[i] == '|')
			if (single_quote == 0 && double_quote == 0)
				shell->pipe_count++;
		if (shell->input[i] == '\'' && double_quote == 0 && single_quote ==  0)
			single_quote = 1;
		else if (shell->input[i] == '\"' && single_quote == 0 && double_quote == 0)
			double_quote = 1;
		else if (shell->input[i] == '\'' && single_quote == 1)
			single_quote = 0;
		else if (shell->input[i] == '\"' && double_quote == 1)
			double_quote = 0;
	}
	return (shell->pipe_count);
}

void	parse_pipes(t_shell *shell)
{
	int	i;
	int	j;
	char	**new_cmd;

	new_cmd = (char **)malloc(sizeof(char *) * (2 + shell->pipe_count));
	if (!new_cmd)
		err("malloc faild");
	init_arr(new_cmd, 2 + shell->pipe_count);
	i = -1;
	j = 0;
	while (shell->input[++i])
	{
		if (shell->input[i] == '|' && shell->input[i + 1])
		{
			i++;
			j++;
		}
		new_cmd[j] = append_char(new_cmd[j], shell->input[i]);
	}
	new_cmd[j + 1] = NULL;//mostlikely not needed
	shell->arr_input = new_cmd;
}

static void manage_fds(t_shell *shell, int *in_fd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (shell->fd[1] != STDOUT_FILENO)
		close(shell->fd[1]);
	*in_fd = shell->fd[0];
}

static void exit_pipes(t_shell *shell, int i, int *in_fd, pid_t *pids)
{
	if (*in_fd != STDIN_FILENO)
        	close(*in_fd);
	shell->retval = check_status(pids[i - 1]);
	free(pids);
	free_arr(shell->arr_input);
}

void	handle_pipes(t_shell *shell)
{
	int	i;
	int	in_fd;
	pid_t *pids;

	in_fd = STDIN_FILENO;
	pids = malloc(arr_len(shell->arr_input) * sizeof(pid_t));
	i = -1;
	while (++i < arr_len(shell->arr_input))
	{
		shell->parsed_cmd = parse_arguments(shell, shell->arr_input[i]);
		check_forbidden_builtin_in_pipe(shell->parsed_cmd, &shell->exit_code);
		if (i < arr_len(shell->arr_input) - 1)
		{
			if (pipe(shell->fd) == -1)
				err("pipe");
		}
		else
			shell->fd[1] = STDOUT_FILENO;
		execute_command(shell, in_fd, shell->fd[1]);
		pids[i] = shell->pid;
		manage_fds(shell, &in_fd);
		free_arr(shell->parsed_cmd);
	}
	exit_pipes(shell, i, &in_fd, pids);
}
