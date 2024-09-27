/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 00:01:09 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/27 14:47:51 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_without_nl(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[i + 1])
		return ;
	while (!ft_strncmp(cmd[++i], "-n", 2) && ((cmd[i][2]) == 'n' || !cmd[i][2]))
		if (!cmd[i + 1])
			return ;
	i--;
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
}

void	ft_echo(char **cmd)
{
	int	i;

	if (arr_len(cmd) == 1)
	{
		printf("\n");
		return ;
	}
	else if (!ft_strncmp(cmd[1], "-n", 2) && ((cmd[1][2]) == 'n' || !cmd[1][2]))
		echo_without_nl(cmd);
	else
	{
		i = 0;
		while (cmd[++i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
		}
		printf("\n");
	}
}
