/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:33:41 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 09:32:00 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_cmd_notfound(char *cmd)
{
	if (!cmd)
		cmd = "0";
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

void	err_nofile(char *file)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}

void	err_is_directory(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
}

void	err_no_permission(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Permission denied\n", 20);
}

void	err_syntax(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token `", 36);
	write(2, cmd, ft_strlen(cmd));
	write(2, "'\n", 2);
}
