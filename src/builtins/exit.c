/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:47:07 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/11 15:13:18 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	ft_putendl_fd("exit", 1);
	if (shell->envp)
		free_arr(shell->envp);
	if (shell->parsed_cmd)
		free_arr(shell->parsed_cmd);
	if (shell->redir->input_file)
		free(shell->redir->input_file);
	if (shell->redir->output_file)
		free(shell->redir->output_file);
	if (shell->redir->here_doc_eof)
		free(shell->redir->here_doc_eof);
	exit(EXIT_SUCCESS);
}
