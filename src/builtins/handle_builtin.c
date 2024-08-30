/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:12:20 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 00:03:05 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_builtin(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd[i], "exit", 4))
			return (1);
		else if (!ft_strncmp(cmd[i], "env", 3))
			return (1);
		else if (!ft_strncmp(cmd[i], "export", 6))
			return (1);
		else if (!ft_strncmp(cmd[i], "unset", 5))
			return (1);
		else if (!ft_strncmp(cmd[i], "echo", 4))
			return (1);
	}
	return (0);
}

char	**exec_builtin(char **cmd, char **envp)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd[i], "exit", 4))
			ft_exit(envp, cmd);
		else if (!ft_strncmp(cmd[i], "env", 3))
			return (ft_env(envp));
		else if (!ft_strncmp(cmd[i], "export", 6))
			return (ft_export(envp, cmd[i + 1]));
		else if (!ft_strncmp(cmd[i], "unset", 5))
			return (ft_unset(envp, cmd[i + 1]));
		else if (!ft_strncmp(cmd[i], "echo", 4))
		{
			ft_echo(cmd);
			break ;
		}
	}
	return (envp);
}
