/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:10:55 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/05 03:19:27 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd_notfound(char **cmd)
{
	err_cmd_notfound(*cmd);
	free_arr(cmd);
	//exit (127);
}

void	exit_is_directory(char **cmd)
{
	err_is_directory(*cmd);
	free_arr(cmd);
	//exit(126);
}

void	exit_no_permission(char **cmd)
{
	err_no_permission(*cmd);
	free_arr(cmd);
	//exit(126);
}

void	exit_no_file(char **cmd)
{
	err_nofile(*cmd);
	free_arr(cmd);
	//exit (127);
}
