/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:56:34 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 22:06:24 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_redir(t_shell *shell, char **parsed_cmd, \
													char *cmd, int *j)
{
	shell->redir->here_doc = 1;
	cmd += 2;
	*j += 1;
	if (*cmd != '\0')
		append_array(cmd, &shell->redir->here_doc_eof, \
							&shell->redir->here_doc_count);
	else if (*(parsed_cmd + 1))
		append_array(*(parsed_cmd + 1), &shell->redir->here_doc_eof, \
										&shell->redir->here_doc_count);
	else
	{
		shell->redir->syntax_err = 0;
		return ;
	}
}

static void	handle_input_file_redir(t_shell *shell, char **parsed_cmd, \
															char *cmd)
{
	cmd += 1;
	if (*cmd != '\0' && !ft_isspace(*cmd))
		append_array(cmd, &shell->redir->input_file, \
					&shell->redir->input_file_count);
	else if (*(parsed_cmd + 1))
		append_array(*(parsed_cmd + 1), &shell->redir->input_file, \
									&shell->redir->input_file_count);
	else
	{
		shell->redir->syntax_err = 0;
		return ;
	}
}

static void	check_syntax_errors(t_shell *shell, char *cmd)
{
	if (ft_strlen(cmd) > 2 && *(cmd + 2) == '<')
		shell->redir->syntax_err = 0;
}

void	validate_input_redir(t_shell *shell, char **parsed_cmd, \
												char *cmd, int *j)
{
	check_syntax_errors(shell, cmd);
	if (*(cmd + 1) == '<')
		handle_heredoc_redir(shell, parsed_cmd, cmd, j);
	else
		handle_input_file_redir(shell, parsed_cmd, cmd);
}
