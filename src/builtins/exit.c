/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:47:07 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/16 14:27:51 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	int i;
	int	exit_code;
	int	j;

	i = 0;
	while (shell->parsed_cmd[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("minishell : exit : too many arguments", 2);
		shell->builtin_exit_code = 1;		
	}
	else
	{
		j = -1;
		while (shell->parsed_cmd[1] && shell->parsed_cmd[1][++j])
		{
			if (ft_isalpha(shell->parsed_cmd[1][j]))
			{
				ft_putendl_fd("exit", 1);
				ft_putstr_fd("minishell : exit : ", 2);
				write(2, shell->parsed_cmd[1], ft_strlen(shell->parsed_cmd[1]));
				ft_putendl_fd(": numeric argument required", 2);
				exit(2);
			}
		}
		ft_putendl_fd("exit", 1);
		if (shell->parsed_cmd[1])
			exit_code = (ft_atoi(shell->parsed_cmd[i - 1])) % 256;
		else
			exit_code = shell->builtin_exit_code;
		free_shell_allocations(shell);
		exit(exit_code);
	}
}
