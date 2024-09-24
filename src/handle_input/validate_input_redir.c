/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:56:34 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 00:03:14 by jmakkone         ###   ########.fr       */
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
	shell->redir->here_doc_eof = ft_realloc(shell->redir->here_doc_eof, \
						 sizeof(char *) * shell->redir->here_doc_count, \
						 sizeof(char *) * (shell->redir->here_doc_count + 1));
	if (shell->redir->here_doc_eof)
		shell->redir->here_doc_eof[shell->redir->here_doc_count] = NULL;
}

static void	handle_input_file_redir(t_shell *shell, char **parsed_cmd, char *cmd)
{
	cmd += 1;
	if (*cmd != '\0')
		append_array(cmd, &shell->redir->input_file, \
			   &shell->redir->input_file_count);
	else if (*parsed_cmd + 1)
		append_array(*(parsed_cmd + 1), &shell->redir->input_file, \
			   &shell->redir->input_file_count);
	shell->redir->input_file = ft_realloc(shell->redir->input_file, \
				   sizeof(char *) * shell->redir->input_file_count, \
				   sizeof(char *) * (shell->redir->input_file_count + 1));
	if (shell->redir->input_file)
		shell->redir->input_file[shell->redir->input_file_count] = NULL;
}

void	validate_input_redir(t_shell *shell, char **parsed_cmd, \
						  						char *cmd, int *j)
{
	if (ft_strlen(cmd) > 2 && *(cmd + 2) == '<')
		exit_syntax_error(shell, "<<");
	if (*(cmd + 1) == '<')
		handle_heredoc_redir(shell, parsed_cmd, cmd, j);
	else
		handle_input_file_redir(shell, parsed_cmd, cmd);
}
