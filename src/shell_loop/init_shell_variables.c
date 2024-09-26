/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:37:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 03:01:12 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(t_shell *shell)
{
	shell->redir->input_file = NULL;
	shell->redir->output_file = NULL;
	shell->redir->here_doc_eof = NULL;
	shell->redir->append_mode = 0;
	shell->redir->input_file_count = 0;
	shell->redir->output_file_count = 0;
	shell->redir->here_doc_count = 0;
	shell->redir->here_doc = 0;
	shell->redir->valid_tokens = NULL;
	shell->redir->token_count = 0;
	shell->redir->token_counter = 0;
	shell->redir->output_file_first = 0;
	shell->redir->syntax_err = -1;
}

static void	init_tilde(t_shell *shell)
{
    int		n_of_slash;
    int		i;
    int		home_end;
    char	*tmp;

    i = -1;
    n_of_slash = 0;
    shell->tilde = getcwd(NULL, 0);
    if (!shell->tilde)
        return ;
    while (shell->tilde[++i])
    {
        if (shell->tilde[i] == '/')
            n_of_slash++;
        if (n_of_slash == 2)
            home_end = i + 1;
    }
    tmp = ft_substr(shell->tilde, 0, home_end);
    free(shell->tilde);
    shell->tilde = tmp;
}

void	init_shell_variables(t_shell *shell)
{
	shell->envp = NULL;
	shell->input = NULL;
	shell->arr_input = NULL;
	shell->parsed_cmd = NULL;
	shell->chained_cmds = NULL;
	shell->tmp_chained_cmds = NULL;
	shell->path = NULL;
	shell->pipe_count = 0;
	shell->chain_count = 0;
	shell->in_pipe = 0;
	shell->is_chained_cmd = 0;
	shell->fd[0] = 0;
	shell->fd[1] = 1;
	shell->pid = -1;
	shell->pids = NULL;
	shell->status = -1;
	shell->retval = 0;
//	shell->builtin_exit_code = 0;
	shell->exit_code = 0;
	shell->last_cmd_in_pipe = 0;
//	shell->prompt = NULL;
	init_tilde(shell);
	init_redir(shell);
}
