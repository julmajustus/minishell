/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:16:15 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/09 12:24:39 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_var(char **envp, char **input_var, int *match_found)
{
	int	j;
	int	k;
	int	len;

	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(envp[j], *input_var, ft_strlen(*input_var)))
		{
			k = 0;
			*match_found = 1;
			len = ft_strlen(*input_var);
			free(*input_var);
			*input_var = NULL;
			*input_var = (char *)malloc(sizeof(char)
					* (ft_strlen(envp[j]) - len));
			while (envp[j][len + 1])
			{
				(*input_var)[k] = envp[j][len + 1];
				k++;
				len++;
			}
			(*input_var)[k] = '\0';
		}
	}
}

static void	exit_status(t_shell shell, char **input_var, int *match_found)
{
	int		i;
	char	*ret_val;
	char	*temp_str;

	i = 0;
	ret_val = ft_itoa(shell.retval);
	temp_str = (char *)malloc(sizeof(char) * ft_strlen(*input_var));
	while ((*input_var)[++i])
		temp_str[i - 1] = (*input_var)[i];
	temp_str[i - 1] = '\0';
	free(*input_var);
	*input_var = NULL;
	*input_var = ft_strjoin(ret_val, temp_str);
	free(ret_val);
	free(temp_str);
	*match_found = 1;
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

void	handle_dollar_sign(t_shell shell, char ***args)
{
	char	**arr;
	int		n;
	int		i;
	int		match_found;

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
				if (arr[i][0] == '?')
					exit_status(shell, &arr[i], &match_found);
				else
					env_var(shell.envp, &arr[i], &match_found);
			}
			check_match(&((*args)[n]), arr, match_found);
			free_arr(arr);
		}
	}
}
