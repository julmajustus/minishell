/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:33:41 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 11:52:29 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	err_cmd_notfound(char *cmd)
{
	write(2, "minishell: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

void	err_nofile(char *file)
{
	write(2, "minishell: ", 7);
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}

void	err_is_directory(char *cmd)
{
	write(2, "minishell: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
}

void	err_no_permission(char *cmd)
{
	write(2, "minishell: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Permission denied\n", 20);
}
