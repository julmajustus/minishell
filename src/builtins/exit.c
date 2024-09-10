/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:47:07 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/10 16:38:11 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	int i;
	int	exit_code;

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
		ft_putendl_fd("exit", 0);
		fflush(stdout);
		exit_code = (ft_atoi(shell->parsed_cmd[i - 1])) % 256;
		free_shell_allocations(shell);
		exit(exit_code);
	}
}
