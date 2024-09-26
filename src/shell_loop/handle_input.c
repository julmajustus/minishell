/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:13:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 09:58:02 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_cmd(t_shell *shell)
{
	init_redir(shell);
	shell->parsed_cmd = parse_arguments(shell, shell->input);
	if (shell->parsed_cmd[0] == NULL || is_empty_str(shell->parsed_cmd[0]))
		return ;
	validate_redirections(shell);
	execute_command(shell, STDIN_FILENO, STDOUT_FILENO);
	shell->retval = check_status(shell->pid);
	free_arr_and_null(&shell->parsed_cmd);
}

static void	clean_allocations(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	shell->input = NULL;
	clean_redir_allocations(shell);
}

void	handle_input(t_shell *shell)
{
	if (shell->input == NULL || is_empty_str(shell->input))
		return ;
	check_if_wildcards(shell);
	if (check_if_chained_cmds(shell))
	{
		parse_chained_cmds(shell);
		handle_chained_cmds(shell);
	}
	else if (check_if_pipes(shell))
	{
		shell->in_pipe = 1;
		parse_pipes(shell);
		handle_pipes(shell);
	}
	else
		handle_single_cmd(shell);
	clean_allocations(shell);
}
