/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:37:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/13 18:18:49 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_redir(t_shell *shell)
{
    shell->redir->input_file = NULL;
    shell->redir->output_file = NULL;
    shell->redir->here_doc_eof = NULL;
    shell->redir->append_mode = 0;
    shell->redir->here_doc = 0;
}

void		init_shell_variables(t_shell *shell)
{
	shell->envp = NULL;
	shell->input = NULL;
	shell->arr_input = NULL;
	shell->parsed_cmd = NULL;
	shell->chained_cmds = NULL;
	shell->chained_tokens = NULL;
	shell->tmp_chained_cmds = NULL;
	shell->tmp_chained_tokens = NULL;
	shell->path = NULL;
	shell->pipe_count = 0;
	shell->chain_count = 0;
	shell->in_pipe = 0;
	shell->is_chained_cmd = 0;
	shell->fd[0] = 0;
	shell->fd[1] = 1;
	shell->pid = -1;
	shell->status = -1;
	shell->retval = -1;
	shell->tilde = getenv("HOME");
	init_redir(shell);
}
