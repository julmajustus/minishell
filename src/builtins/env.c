/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:03:00 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/29 23:33:27 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env(char **envp)
{
	int i;

	i = -1;
	if (!envp || !*envp)
		return (NULL);
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (envp);
}
