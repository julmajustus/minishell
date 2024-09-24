/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_allocations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:19:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/23 13:22:55 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void clean_child_redir_allocations(t_shell *shell)
{
	if (shell->redir->input_file)
		free(shell->redir->input_file);
	if (shell->redir->output_file)
		free(shell->redir->output_file);
	if (shell->redir->here_doc_eof)
		free(shell->redir->here_doc_eof);
}

static void	clean_child_chained_cmds(t_shell *shell)
{
	if (shell->is_builtin && shell->is_chained_cmd)
	{
		if (shell->preserving_chained_cmds)
			free_cmd_stack(&shell->cmd_stack);
		free_arr_and_null(&shell->chained_cmds);
	}
}

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
	if (shell->input)
		free(shell->input);
	if (shell->prompt)
		free(shell->prompt);
	clean_child_redir_allocations(shell);
	clean_child_chained_cmds(shell);
}
