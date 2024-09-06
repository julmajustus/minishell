/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:58:30 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 09:25:01 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_pipes(t_shell *shell)
{
	int i;

	shell->pipe_count = 0;
	i = -1;
	while (shell->input[++i])
	{
		if (shell->input[i] == '|')
			shell->pipe_count++;
	}
	return (shell->pipe_count);
}

void	parse_pipes(t_shell *shell)
{
	int	i;
	int	j;
	char **new_cmd;

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


void	handle_pipes(t_shell *shell)
{
	int	i;
	int	in_fd = STDIN_FILENO;

	i = -1;
	while (++i < arr_len(shell->arr_input))
	{
		shell->parsed_cmd = parse_arguments(shell, shell->arr_input[i]);
		if (i < arr_len(shell->arr_input) - 1)
		{
			if (pipe(shell->fd) == -1)
				err("pipe");
		}
		else
			shell->fd[1] = STDOUT_FILENO;
		execute_command(shell, in_fd, shell->fd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (shell->fd[1] != STDOUT_FILENO)
			close(shell->fd[1]);
		in_fd = shell->fd[0];
		free_arr(shell->parsed_cmd);
	}
	if (in_fd != STDIN_FILENO)
        	close(in_fd);
	free_arr(shell->arr_input);
}
