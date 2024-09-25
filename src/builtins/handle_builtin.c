/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:12:20 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/25 18:38:02 by jmakkone         ###   ########.fr       */
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

char	**exec_builtin(t_shell *shell, int parent, int child)
{
	int	i;

	i = -1;
	while (shell->parsed_cmd[++i])
	{
		if (!ft_strcmp(shell->parsed_cmd[i], "exit") && parent == 1)
		{
			ft_exit(shell);
			break ;
		}
		else if (!ft_strcmp(shell->parsed_cmd[i], "env") && child == 1)
			return (ft_env(shell->envp));
		else if (!ft_strcmp(shell->parsed_cmd[i], "export") && parent == 1)
			return (ft_export(shell->envp, shell->parsed_cmd[i + 1], &shell->exit_code));
		else if (!ft_strcmp(shell->parsed_cmd[i], "unset") && parent == 1)
			return (ft_unset(shell->envp, shell->parsed_cmd[i + 1]));
		else if (!ft_strcmp(shell->parsed_cmd[i], "echo") && child == 1)
		{
			ft_echo(shell->parsed_cmd);
			break ;
		}
		else if (!ft_strcmp(shell->parsed_cmd[i], "pwd") && child == 1)
		{
			ft_pwd(shell->envp);
			break;
		}
		else if (!ft_strcmp(shell->parsed_cmd[i], "cd") && parent == 1)
			return(ft_cd(shell->envp, shell->parsed_cmd[i + 1], \
				&shell->exit_code, &shell->builtin_already_executed, shell->parsed_cmd));
	}
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

void	check_forbidden_builtin_in_pipe(char **cmd_arr, int *exit_code)
{
	int i;

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
