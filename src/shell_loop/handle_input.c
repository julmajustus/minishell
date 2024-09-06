/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:13:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 19:23:38 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void handle_single_cmd(t_shell *shell)
{
	shell->parsed_cmd = parse_arguments(shell, shell->input);
	execute_command(shell, STDIN_FILENO, STDOUT_FILENO);
	free_arr(shell->parsed_cmd);
}

void	handle_input(t_shell *shell)
{
	if (shell->input == NULL || is_empty_str(shell->input))
		return;
	if (check_if_pipes(shell))
	{
		shell->in_pipe = 1;
		parse_pipes(shell);
		handle_pipes(shell);
	}
	else
	{
		shell->in_pipe = 0;
		handle_single_cmd(shell);
	}
	free(shell->input);
	shell->input = NULL;
}
