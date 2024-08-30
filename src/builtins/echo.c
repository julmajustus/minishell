/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 00:01:09 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 01:41:00 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	
	if (arr_len(cmd) == 1)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	else if (!ft_strncmp(cmd[1], "-n", 2))
	{
		i = 1;
		while (cmd[++i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		i = 0;
		while (cmd[++i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd('\n', 1);
	}
}
