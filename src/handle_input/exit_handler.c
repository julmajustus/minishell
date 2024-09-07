/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:10:55 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/07 22:27:42 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd_notfound(t_shell *shell)
{
	err_cmd_notfound(shell->parsed_cmd[0]);
	free_shell_allocations(shell);
	exit (127);
}

void	exit_is_directory(t_shell *shell)
{
	err_is_directory(shell->parsed_cmd[0]);
	free_shell_allocations(shell);
	exit(126);
}

void	exit_no_permission(t_shell *shell)
{
	err_no_permission(shell->parsed_cmd[0]);
	free_shell_allocations(shell);
	exit(126);
}

void	exit_no_file(t_shell *shell)
{
	err_nofile(shell->parsed_cmd[0]);
	free_shell_allocations(shell);
	exit (127);
}

void	exit_syntax_error(t_shell *shell, char *syntax)
{
	err_syntax(syntax);
	free_shell_allocations(shell);
	exit (2);
}
