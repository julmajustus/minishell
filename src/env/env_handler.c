/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:27:02 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/28 14:06:44 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char **modify_envp(char **old_envp, char *env)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strchr())
		i++;
	}
	new_envp[i] = NULL;
}

char **copy_envp(char **envp)
{
	int i;
	char **new_envp;
	
	i = 0;
	new_envp = (char **)malloc((sizeof(char) * arr_len(envp)) + 1);
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
