/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:34:23 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/02 17:35:36 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_variable_name(char *str)
{
	int	i;

	i = 0;
	if (!ft_strchr(str, '='))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]) || str[i] != '_')
			i++;
		else
			return (0);
	}
	return (1);
}

char	**ft_export(char **envp, char *str)
{
	int	i;
	int	j;

	if (!str || !*str)
	{
		i = -1;
		while (envp[++i])
		{
			j = 0;
			while (envp[i][j] != '=')
				j++;
			printf("declare -x %.*s\"%s\"\n", j + 1, envp[i], envp[i] + j + 1);
		}
		return (envp);
	}
	if (is_valid_variable_name(str))
		return (replace_or_create_env_line(envp, str));
	return (envp);
}
