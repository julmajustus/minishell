/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:44:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/07 22:39:15 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	validate_input_redir(t_shell *shell, char **parsed_cmd, char *cmd)
{
	if (*(cmd + 1) == '<')
	{
		if (*(cmd + 2) == '<')
			exit_syntax_error(shell, "<<");
		shell->redir->here_doc = 1;
		if (*(cmd + 2) != '\0')
			shell->redir->here_doc_eof = ft_strdup(cmd + 2);
		else if (*(parsed_cmd + 1))
			shell->redir->here_doc_eof = ft_strdup(*(parsed_cmd + 1));
	}
	else
	{
		if (*(cmd + 1) != '\0')
			shell->redir->input_file = ft_strdup(cmd + 1);
		else if (*parsed_cmd + 1)
			shell->redir->input_file = ft_strdup(*(parsed_cmd + 1));
	}
}

static void	validate_output_redir(t_shell *shell, char **parsed_cmd, char *cmd)
{
	if (*(cmd + 1) == '>')
	{
		if (*(cmd + 2) == '>')
			exit_syntax_error(shell, ">>");
		shell->redir->append_mode = 1;
		if (*(cmd + 2) != '\0')
			shell->redir->output_file = ft_strdup(cmd + 2);
		else if (*(parsed_cmd + 1))
			shell->redir->output_file = ft_strdup(*(parsed_cmd + 1));
	}
	else if (!shell->redir->append_mode)
	{
		shell->redir->append_mode = 0;
		if (*(cmd + 1) != '\0')
			shell->redir->output_file = ft_strdup(cmd + 1);
		else if (*(parsed_cmd + 1))
			shell->redir->output_file = ft_strdup(*(parsed_cmd + 1));
	}
}


void validate_redirections(t_shell *shell)
{	
	char *cmd;
	int i;
	int j;

	i = 0;
	while (shell->parsed_cmd[i])
	{
		cmd = shell->parsed_cmd[i];
		j = 0;
		while (cmd[j])
		{
			if (cmd[j] == '<')
				validate_input_redir(shell, &shell->parsed_cmd[i], &cmd[j]);
			else if (cmd[j] == '>')
				validate_output_redir(shell, &shell->parsed_cmd[i], &cmd[j]);
			j++;
		}
		i++;
	}
	if (shell->redir->input_file || shell->redir->output_file)
		parse_redirections(shell);
}
