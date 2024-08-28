/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:47:35 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/28 14:03:52 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
int	main(int ac, char **av, char **envp)
{
	char **envp_copy;

	if (ac != 1)
		return (0);
	(void)av;
	envp_copy = copy_envp(envp);

	int i = 0;
	while (envp_copy[i])
	{
		printf("%s\n", envp_copy[i]);
		i++;
	}
	return (0);
}
