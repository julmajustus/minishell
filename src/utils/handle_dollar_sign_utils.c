/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:02:37 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/30 13:06:26 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_space(char **input_var)
{
	char	*temp;

	temp = ft_strjoin(*input_var, " ");
	free(*input_var);
	*input_var = temp;
}

void	replace_env_var(char **envp, char **temp_var, int *match_found)
{
	int	j;
	int	k;
	int	len;

	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(envp[j], *temp_var, ft_strlen(*temp_var)))
		{
			k = 0;
			*match_found = 1;
			len = ft_strlen(*temp_var);
			free(*temp_var);
			*temp_var = NULL;
			*temp_var = (char *)malloc(sizeof(char)
					* (ft_strlen(envp[j]) - len));
			while (envp[j][len + 1])
			{
				(*temp_var)[k] = envp[j][len + 1];
				k++;
				len++;
			}
			(*temp_var)[k] = '\0';
		}
	}
}

void	remove_empty_args(char ***args)
{
	int		i;
	int		j;
	int		count;
	char	**new_args;

	i = -1;
	count = 0;
	while ((*args)[++i])
		if (ft_strlen((*args)[i]) > 0)
			count++;
	new_args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return ;
	i = -1;
	j = -1;
	while ((*args)[++i])
		if (ft_strlen((*args)[i]) > 0)
			new_args[++j] = ft_strdup((*args)[i]);
	new_args[++j] = NULL;
	free_arr(*args);
	*args = new_args;
}
