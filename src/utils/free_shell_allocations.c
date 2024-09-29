/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell_allocations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:19:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 21:10:14 by jmakkone         ###   ########.fr       */
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
		free_and_null((void *)&shell->redir->valid_tokens);
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
		free_arr_and_null(&shell->envp);
	if (shell->pending_exports)
		free_arr_and_null(&shell->pending_exports);
	if (shell->parsed_cmd)
		free_arr_and_null(&shell->parsed_cmd);
	if (shell->path)
		free_and_null((void *)&shell->path);
	if (shell->piped_cmds)
		free_arr_and_null(&shell->piped_cmds);
	if (shell->input)
		free_and_null((void *)&shell->input);
	if (shell->tilde)
		free_and_null((void *)&shell->tilde);
	if (shell->pids)
		free_and_null((void *)&shell->pids);
	if (shell->prompt)
		free_and_null((void *)&shell->prompt);
	clean_redir_allocations(shell);
	clean_child_chained_cmds(shell);
	rl_clear_history();
}
