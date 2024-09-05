/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:37:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/05 05:54:11 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_shell_variables(t_shell *shell)
{
//	shell->envp = NULL;
	shell->input = NULL;
	shell->arr_input = NULL;
	shell->parsed_cmd = NULL;
	shell->path = NULL;
	shell->pipe_count = 0;
	shell->in_pipe = 0;
	shell->fd[0] = -1;
	shell->fd[1] = -1;
	shell->pid = -1;
	shell->status = -1;
	shell->retval = -1;
}

t_redir	*init_redir(void)
{
    t_redir *redir;

	redir = malloc(sizeof(t_redir));
    redir->input_file = NULL;
    redir->output_file = NULL;
    redir->append_mode = 0;
    redir->here_doc = 0;
    return redir;
}

