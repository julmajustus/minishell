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

static int	is_valid_variable_name(char *str, int **exit_code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[0]) || (str[0] == '=' && !str[1]))
		{
			ft_putendl_fd(" not a valid identifier", 2);
			**exit_code = 1;
			return (0);
		}
		else if (ft_isalpha(str[i]) || str[i] == '_')
			i++;
		else
		{
			ft_putendl_fd(" not a valid identifier", 2);
			**exit_code = 1;
			return (0);
		}
		if (str[i] == '=' && str[i + 1])
			break ;
	}
	if (!ft_strchr(str, '='))
		return (0);
	return (1);
}

char	**ft_export(char **envp, char *str, int *exit_code)
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
	if (is_valid_variable_name(str, &exit_code))
		return (replace_or_create_env_line(envp, str));
	return (envp);
}
