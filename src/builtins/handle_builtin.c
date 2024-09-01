/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:12:20 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 23:40:58 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_builtin(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strcmp(cmd[i], "exit"))
			return (1);
		else if (!ft_strcmp(cmd[i], "env"))
			return (1);
		else if (!ft_strcmp(cmd[i], "export"))
			return (1);
		else if (!ft_strcmp(cmd[i], "unset"))
			return (1);
		else if (!ft_strcmp(cmd[i], "echo"))
			return (1);
		else if (!ft_strcmp(cmd[i], "pwd"))
			return (1);
		else if (!ft_strcmp(cmd[i], "cd"))
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
		if (!ft_strcmp(cmd[i], "exit"))
			ft_exit(envp, cmd);
		else if (!ft_strcmp(cmd[i], "env"))
			return (ft_env(envp));
		else if (!ft_strcmp(cmd[i], "export"))
			return (ft_export(envp, cmd[i + 1]));
		else if (!ft_strcmp(cmd[i], "unset"))
			return (ft_unset(envp, cmd[i + 1]));
		else if (!ft_strcmp(cmd[i], "echo"))
		{
			ft_echo(cmd);
			break ;
		}
		else if (!ft_strcmp(cmd[i], "pwd"))
		{
			ft_pwd(envp);
			break;
		}
		else if (!ft_strcmp(cmd[i], "cd"))
			return(ft_cd(envp, cmd[i + 1]));
	}
	return (envp);
}
