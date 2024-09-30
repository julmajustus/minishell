/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_forbidden_builtin_in_pipe.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:24:50 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 17:25:06 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_forbidden_builtin_in_pipe(char **cmd_arr, int *exit_code)
{
	int	i;

	i = -1;
	while (cmd_arr[++i])
	{
		if (!ft_strcmp(cmd_arr[0], "exit"))
			*exit_code = 1;
		else if (!ft_strcmp(cmd_arr[0], "export"))
			*exit_code = 1;
		else if (!ft_strcmp(cmd_arr[0], "unset"))
			*exit_code = 1;
		else if (!ft_strcmp(cmd_arr[0], "cd"))
			*exit_code = 1;
	}
}
