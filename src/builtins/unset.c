/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:45:45 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 20:45:21 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(char **envp, char *str)
{
	int	i;

	if (!str || !*str || ft_strchr(str, '='))
		return (envp);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0 && 
			envp[i][ft_strlen(str)] == '=')
			return (delete_env_line(envp, str));
	}
	return (envp);
}
