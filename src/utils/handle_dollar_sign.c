/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:16:15 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/23 02:39:15 by jmakkone         ###   ########.fr       */
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
	//ret_val = ft_itoa(shell.builtin_exit_code);
	ret_val = ft_itoa(shell.retval); //need to some how handle both builtin and external cmd returnvalues
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

static void	check_match(char **input_var, char **arr, int match_found, int space)
{
	int	i;

/*	if (!match_found)
	{
		free(*input_var);
		*input_var = (char *)malloc(sizeof(char) * 1);
		*(input_var)[0] = '\0';
	}*/
	if (match_found)
	{
		i = 0;
		free(*input_var);
		*input_var = NULL;
		*input_var = ft_strdup(arr[i]);
		while (arr[++i])
		{
			if (space)
				*input_var = ft_strjoin(*input_var, " ");
			*input_var = ft_strjoin(*input_var, arr[i]);
		}
	}
}

void	handle_dollar_sign(t_shell shell, char ***args)
{
	char	**arr;
	int		n;
	int		i;
	int		match_found;
	int		j;
	char	**arr_1;

	n = -1;
	while ((*args)[++n])
	{
		if (ft_strchr((*args)[n], '$') && ft_strcmp((*args)[n], "$"))
		{
			arr_1 = ft_split((*args)[n], ' ');
			j = -1;
			while (arr_1[++j])
			{
				match_found = 0;
				arr = ft_split(arr_1[j], '$');
				i = -1;
				while (arr[++i])
				{
					if (arr[i][0] == '?')
						exit_status(shell, &arr[i], &match_found);
					else
						env_var(shell.envp, &arr[i], &match_found);
				}
				check_match(&arr_1[j], arr, match_found, 0);
				free_arr(arr);
			}
			check_match(&((*args)[n]), arr_1, match_found, 1);
			free_arr(arr_1);
		}
	}
}
