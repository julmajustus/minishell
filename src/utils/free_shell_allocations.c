/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_allocations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:19:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 01:37:19 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell_allocations(t_shell *shell)
{
	if (shell->envp)
		free_arr(shell->envp);
	if (shell->parsed_cmd)
		free_arr(shell->parsed_cmd);
	if (shell->path)
		free(shell->path);
	if (shell->in_pipe)
		free_arr(shell->arr_input);
	else
		free(shell->input);
	if (shell->redir->input_file)
		free(shell->redir->input_file);
	if (shell->redir->output_file)
		free(shell->redir->output_file);
	free(shell->redir);
}
