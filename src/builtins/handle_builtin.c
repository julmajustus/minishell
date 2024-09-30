/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:12:20 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 17:47:17 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_builtin(t_shell *shell)
{
	if (!shell->parsed_cmd || !shell->parsed_cmd[0])
		return (0);
	if (!ft_strcmp(shell->parsed_cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(shell->parsed_cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(shell->parsed_cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(shell->parsed_cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(shell->parsed_cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(shell->parsed_cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(shell->parsed_cmd[0], "cd"))
		return (1);
	return (0);
}

static char	**handle_unset(t_shell *shell)
{
	int	i;
	
	i = 0;
	if (!shell->parsed_cmd[i + 1])
		shell->envp = ft_unset(shell, NULL);
	else
	{
		while (shell->parsed_cmd[++i])
			shell->envp = ft_unset(shell, shell->parsed_cmd[i]);
	}
	return (shell->envp);
}

static char	**handle_export(t_shell *shell)
{
	int	i;
	
	i = 0;
	if (!shell->parsed_cmd[i + 1])
		shell->envp = ft_export(shell, NULL);
	else
	{
		while (shell->parsed_cmd[++i])
			shell->envp = ft_export(shell, shell->parsed_cmd[i]);
	}
	return (shell->envp);
}

char	**exec_builtin(t_shell *shell, int parent, int child)
{
	if (!ft_strcmp(shell->parsed_cmd[0], "exit") && parent == 1)
		ft_exit(shell);
	else if (!ft_strcmp(shell->parsed_cmd[0], "env") && child == 1)
		return (ft_env(shell->envp, shell->parsed_cmd, &shell->exit_code));
	else if (!ft_strcmp(shell->parsed_cmd[0], "export") && parent == 1)
		return (handle_export(shell));
	else if (!ft_strcmp(shell->parsed_cmd[0], "unset") && parent == 1)
		return (handle_unset(shell));
	else if (!ft_strcmp(shell->parsed_cmd[0], "echo") && child == 1)
		ft_echo(shell->parsed_cmd);
	else if (!ft_strcmp(shell->parsed_cmd[0], "pwd") && child == 1)
		ft_pwd(shell->envp);
	else if (!ft_strcmp(shell->parsed_cmd[0], "cd") && parent == 1)
		return (ft_cd(shell, shell->parsed_cmd[1]));
	return (shell->envp);
}

void	handle_builtin(t_shell *shell, int parent, int child)
{
	if (!shell->parsed_cmd || !*shell->parsed_cmd)
		return ;
	if ((shell->in_pipe || shell->builtin_already_executed) && \
		!ft_strcmp(shell->parsed_cmd[0], "cd"))
		return ;
	if (shell->in_pipe && !ft_strcmp(shell->parsed_cmd[0], "exit"))
		return ;
	shell->envp = exec_builtin(shell, parent, child);
}
