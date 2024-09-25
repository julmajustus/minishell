/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:24:31 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 13:27:33 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_redir		redir;
	t_cmd_stack	cmd_stack;

	(void)argc;
	(void)argv;
	shell.cmd_stack = &cmd_stack;
	shell.redir = &redir;
	init_shell_variables(&shell);
	shell.envp = copy_env(envp);
	init_signals();
	shell_loop(&shell);
	return (0);
}
