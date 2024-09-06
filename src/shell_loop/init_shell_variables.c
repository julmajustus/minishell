/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:37:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 19:43:18 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_redir(t_shell *shell)
{
    shell->redir->input_file = NULL;
    shell->redir->output_file = NULL;
    shell->redir->append_mode = 0;
    shell->redir->here_doc = 0;
}

void		init_shell_variables(t_shell *shell)
{
	shell->envp = NULL;
	shell->input = NULL;
	shell->arr_input = NULL;
	shell->parsed_cmd = NULL;
	shell->path = NULL;
	shell->pipe_count = 0;
	shell->in_pipe = 0;
	shell->fd[0] = 0;
	shell->fd[1] = 1;
	shell->pid = -1;
	shell->status = -1;
	shell->retval = -1;
	init_redir(shell);
}
