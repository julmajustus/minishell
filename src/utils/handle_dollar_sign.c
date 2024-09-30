/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:16:15 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/30 13:07:27 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_var(char **envp, char **input_var, int *match_found)
{
	int		j;
	int		k;
	char	*temp_var;
	char	*temp_input_var;

	temp_var = (char *)malloc(sizeof(char) * (ft_strlen(*input_var) + 1));
	j = -1;
	k = -1;
	while ((*input_var)[++j])
		if (ft_isalnum((*input_var)[j]) || (*input_var)[j] == '_')
			temp_var[++k] = (*input_var)[j];
	temp_var[++k] = '\0';
	temp_input_var = ft_strtrim(*input_var, temp_var);
	replace_env_var(envp, &temp_var, match_found);
	free(*input_var);
	*input_var = ft_strjoin(temp_var, temp_input_var);
	free(temp_input_var);
	free(temp_var);
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

static void	check_match(char **input_var, char **arr, \
		int match_found, int space)
{
	int		i;
	char	*temp;

	if (!match_found && !ft_strcmp(*input_var, arr[0]) && arr[0][0] == '$')
	{
		free(*input_var);
		*input_var = ft_strdup("");
	}
	if (match_found)
	{
		i = 0;
		free(*input_var);
		*input_var = NULL;
		*input_var = ft_strdup(arr[i]);
		while (arr[++i])
		{
			if (space)
				add_space(input_var);
			temp = ft_strjoin(*input_var, arr[i]);
			free(*input_var);
			*input_var = temp;
		}
	}
}

void	check_if_exit_or_env_var(char **arr_1, t_shell shell, int *match_found)
{
	int		j;
	int		i;
	char	**arr;

	j = -1;
	while (arr_1[++j])
	{
		arr = ft_split(arr_1[j], '$');
		i = -1;
		while (arr[++i])
		{
			*match_found = 0;
			if (arr[i][0] == '?')
				exit_status(shell, &arr[i], match_found);
			else if (ft_isalpha(arr[i][0]) || arr[i][0] == '_')
				env_var(shell.envp, &arr[i], match_found);
		}
		if (arr[0] && ft_strlen(arr[0]) > 0)
			check_match(&arr_1[j], arr, *match_found, 0);
		free_arr_and_null(&arr);
	}
}

void	handle_dollar_sign(t_shell shell, char ***args)
{
	int		n;
	int		match_found;
	char	**arr_1;

	n = -1;
	while ((*args)[++n])
	{
		if (ft_strchr((*args)[n], '$') && ft_strcmp((*args)[n], "$"))
		{
			arr_1 = ft_split((*args)[n], ' ');
			check_if_exit_or_env_var(arr_1, shell, &match_found);
			check_match(&((*args)[n]), arr_1, match_found, 1);
			free_arr_and_null(&arr_1);
		}
	}
	remove_empty_args(args);
}
