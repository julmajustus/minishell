/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:13:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/02 23:29:19 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void handle_builtin(t_shell *shell)
{
	shell->envp = exec_builtin(shell->arr_input, shell->envp);
	free(shell->input);
	free_arr(shell->arr_input);
	shell->path = NULL;
}

static	void handle_external_cmd(t_shell *shell)
{
			shell->path = create_path(shell->arr_input, shell->envp);
			if (shell->path)
			{
				shell->pid = fork();
				if (shell->pid == -1)
					exit(EXIT_FAILURE);
				if (shell->pid == 0)
				{
					execve(shell->path, shell->arr_input, shell->envp);
					exit(EXIT_FAILURE);
				}
				else
					waitpid(shell->pid, &shell->status, 0);
				free(shell->input);
				free_arr(shell->arr_input);
				free(shell->path);
			}
}

void	handle_input(t_shell *shell)
{
			if (check_if_builtin(shell->arr_input))
				handle_builtin(shell);
			else
				handle_external_cmd(shell);
}
