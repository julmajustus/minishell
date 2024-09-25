/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_allocations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:19:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 02:44:39 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_redir_allocations(t_shell *shell)
{
	if (shell->redir->input_file)
		free_arr_and_null(&shell->redir->input_file);
	if (shell->redir->output_file)
		free_arr_and_null(&shell->redir->output_file);
	if (shell->redir->here_doc_eof)
		free_arr_and_null(&shell->redir->here_doc_eof);
	if (shell->redir->valid_tokens)
		free(shell->redir->valid_tokens);
	shell->redir->valid_tokens = NULL;
}

static void	clean_child_chained_cmds(t_shell *shell)
{
	if (shell->is_chained_cmd)
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
	if (shell->tilde)
		free(shell->tilde);
	if (shell->pids)
		free(shell->pids);
	shell->pids = NULL;
	clean_redir_allocations(shell);
	clean_child_chained_cmds(shell);
}
