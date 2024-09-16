/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:37:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/16 14:00:57 by mpellegr         ###   ########.fr       */
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

static void	init_tilde(t_shell *shell)
{
	int	n_of_slash;
	int	i;
	int	home_end;

	i = -1;
	n_of_slash = 0;
	shell->tilde = getcwd(NULL, 0);
	while (shell->tilde[++i])
	{
		if (shell->tilde[i] == '/')
			n_of_slash++;
		if (n_of_slash == 2)
			home_end = i + 1;
	}
	shell->tilde = ft_substr(shell->tilde, 0, home_end);
}

void	init_shell_variables(t_shell *shell)
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
	shell->builtin_exit_code = 0;
	init_tilde(shell);
	init_redir(shell);
}
