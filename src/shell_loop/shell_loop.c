/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:34:38 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/20 22:13:13 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell *shell)
{
	while (1)
	{
		shell->cmd_stack = NULL;
		shell->execute_next = 1;
		shell->is_builtin = 0;
		shell->is_chained_cmd = 0;
		shell->preserving_chained_cmds = 0;
		shell->exit_code = 0;
		shell->pipe_count = 0;
		shell->fd[0] = STDIN_FILENO;
		shell->fd[1] = STDOUT_FILENO;
		shell->last_cmd_in_pipe = 0;
//		shell->builtin_exit_code = 0;
		shell->builtin_already_executed = 0;
		init_redir(shell);
		prompt(shell);
		handle_input(shell);
	}
}
