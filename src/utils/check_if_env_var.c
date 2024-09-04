/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:16:15 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/04 14:16:17 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_env_var(char *envp_var, char **input_var, int *match_found)
{
	int	k;
	int	len;

	k = 0;
	*match_found = 1;
	len = ft_strlen(*input_var);
	free(*input_var);
	*input_var = NULL;
	*input_var = (char *)malloc(sizeof(char) * (ft_strlen(envp_var) - len));
	while (envp_var[len + 1])
	{
		(*input_var)[k] = envp_var[len + 1];
		k++;
		len++;
	}
	(*input_var)[k] = '\0';
}

static void	check_match(char **input_var, char **arr, int match_found)
{
	int	i;

	if (!match_found)
	{
		free(*input_var);
		*input_var = (char *)malloc(sizeof(char) * 1);
		*(input_var)[0] = '\0';
	}
	else
	{
		i = 0;
		free(*input_var);
		*input_var = NULL;
		*input_var = ft_strdup(arr[i]);
		while (arr[++i])
			*input_var = ft_strjoin(*input_var, arr[i]);
	}
}

void	check_if_env_var(char **envp, char ***args)
{
	char	**arr;
	int		n;
	int		i;
	int		match_found;
	int		j;

	n = -1;
	while ((*args)[++n])
	{
		if (ft_strchr((*args)[n], '$'))
		{
			match_found = 0;
			arr = ft_split((*args)[n], '$');
			i = -1;
			while (arr[++i])
			{
				j = -1;
				while (envp[++j])
					if (!ft_strncmp(envp[j], arr[i], ft_strlen(arr[i])))
						replace_env_var(envp[j], &arr[i], &match_found);
			}
			check_match(&((*args)[n]), arr, match_found);
			free_arr(arr);
		}
	}
}
