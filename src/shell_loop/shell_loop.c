/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:34:38 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/01 11:43:34 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_shell *shell)
{
	while (1)
	{
		shell->cmd_stack = NULL;
		shell->execute_next = 1;
		shell->is_chained_cmd = 0;
		shell->preserving_chained_cmds = 0;
		shell->exit_code = 0;
		shell->pipe_count = 0;
		shell->fd[0] = STDIN_FILENO;
		shell->fd[1] = STDOUT_FILENO;
		shell->last_cmd_in_pipe = 0;
		prompt(shell);
		handle_input(shell);
	}
}
