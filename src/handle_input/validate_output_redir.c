/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_output_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:05:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 22:04:04 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_syntax_errors(t_shell *shell, char *cmd)
{
	if (ft_strlen(cmd) > 2 && *(cmd + 2) == '>')
		shell->redir->syntax_err = 1;
}

void	validate_output_redir(t_shell *shell, char **parsed_cmd, \
												char *cmd, int *j)
{
	check_syntax_errors(shell, cmd);
	if (*(cmd + 1) == '>')
	{
		shell->redir->append_mode = 1;
		cmd += 2;
		*j += 1;
	}
	else
	{
		shell->redir->append_mode = 0;
		cmd += 1;
	}
	if (*cmd != '\0')
		append_array(cmd, &shell->redir->output_file, \
			&shell->redir->output_file_count);
	else if (*(parsed_cmd + 1))
		append_array(*(parsed_cmd + 1), &shell->redir->output_file, \
			&shell->redir->output_file_count);
	else
	{
		shell->redir->syntax_err = 1;
		return ;
	}
}
