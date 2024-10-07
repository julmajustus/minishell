/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:47:07 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/04 12:16:20 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_too_many_arguments(void)
{
	ft_putendl_fd("exit", 1);
	ft_putendl_fd("minishell : exit : too many arguments", 2);
	return (1);
}

static void	exit_numeric_arg_required(t_shell *shell)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell : exit : ", 2);
	write(2, shell->parsed_cmd[1], ft_strlen(shell->parsed_cmd[1]));
	ft_putendl_fd(": numeric argument required", 2);
	free_shell_allocations(shell);
	exit(2);
}

void	ft_exit(t_shell *shell)
{
	int	i;
	int	exit_code;
	int	j;

	i = 0;
	while (shell->parsed_cmd[i])
		i++;
	if (i > 2)
		shell->exit_code = exit_too_many_arguments();
	else
	{
		j = -1;
		while (shell->parsed_cmd[1] && shell->parsed_cmd[1][++j])
			if (!ft_isdigit(shell->parsed_cmd[1][j]) && \
			shell->parsed_cmd[1][0] != '-' && shell->parsed_cmd[1][0] != '+')
				exit_numeric_arg_required(shell);
		ft_putendl_fd("exit", 1);
		if (shell->parsed_cmd[1])
			exit_code = (ft_atoi(shell->parsed_cmd[i - 1])) % 256;
		else
			exit_code = shell->retval;
		free_shell_allocations(shell);
		exit(exit_code);
	}
}
