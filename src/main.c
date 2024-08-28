/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:47:35 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/28 17:32:51 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "env.h"
#include "minishell.h"
#include <stdio.h>
int	main(int ac, char **av, char **envp)
{
	char **envp_copy;

	if (ac != 1)
		return (0);
	(void)av;
	envp_copy = copy_env(envp);
	envp_copy = replace_or_create_env_line(envp_copy, "SALLE=abugalgaga");
	//envp_copy = delete_env_line(envp_copy, "SALLE");

	int i = 0;
	while (envp_copy[i])
	{
		printf("%s\n", envp_copy[i]);
		i++;
	}
	return (0);
}
