/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:15:36 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 16:04:38 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_cmd(char *cmd)
{
	int	fd;

	if (is_empty_str(cmd))
		return (1);
	if (ft_strchr(cmd, '/') != NULL)
	{
		fd = open(cmd, O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			return (2);
		}
	}
	return (0);
}

void	validate_cmd(t_shell *shell)
{
	int		cmd_check;

	if (!shell->parsed_cmd || !shell->parsed_cmd[0])
	{
//		if (shell->in_pipe && !shell->redir->here_doc)
//			exit_syntax_error(shell, "|");
		exit_cmd_notfound(shell);	
	}
	cmd_check = check_cmd(shell->parsed_cmd[0]);
	if (cmd_check == 1)
		exit_cmd_notfound(shell);
	else if (cmd_check == 2)
		exit_is_directory(shell);
}
