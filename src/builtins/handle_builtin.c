/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:12:20 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/12 23:33:56 by jmakkone         ###   ########.fr       */
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

char	**exec_builtin(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->parsed_cmd[++i])
	{
		if (!ft_strcmp(shell->parsed_cmd[i], "exit"))
			ft_exit(shell);
		else if (!ft_strcmp(shell->parsed_cmd[i], "env"))
			return (ft_env(shell->envp));
		else if (!ft_strcmp(shell->parsed_cmd[i], "export"))
			return (ft_export(shell->envp, shell->parsed_cmd[i + 1]));
		else if (!ft_strcmp(shell->parsed_cmd[i], "unset"))
			return (ft_unset(shell->envp, shell->parsed_cmd[i + 1]));
		else if (!ft_strcmp(shell->parsed_cmd[i], "echo"))
		{
			ft_echo(shell->parsed_cmd);
			break ;
		}
		else if (!ft_strcmp(shell->parsed_cmd[i], "pwd"))
		{
			ft_pwd(shell->envp);
			break;
		}
		else if (!ft_strcmp(shell->parsed_cmd[i], "cd"))
			return(ft_cd(shell->envp, shell->parsed_cmd[i + 1], \
				&shell->builtin_exit_code, &shell->builtin_already_executed));
	}
	return (shell->envp);
}

void	handle_builtin(t_shell *shell)
{
	if ((shell->in_pipe || shell->builtin_already_executed) && \
		!ft_strcmp(shell->parsed_cmd[0], "cd"))
		return ;
	if (shell->in_pipe && !ft_strcmp(shell->parsed_cmd[0], "exit"))
		return ;
	shell->envp = exec_builtin(shell);
}
