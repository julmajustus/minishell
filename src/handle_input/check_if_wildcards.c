/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:49:34 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/23 02:20:10 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_wildcards(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	if(ft_strchr(shell->input, '*'))
	{
		shell->parsed_cmd = ft_split(shell->input, ' ');
		handle_wildcards(shell);
		free(shell->input);
		shell->input = ft_strdup("");
		while (shell->parsed_cmd[++i])
		{
			tmp = shell->input;
			shell->input = ft_strjoin(tmp, shell->parsed_cmd[i]);
			free(tmp);
			if (shell->parsed_cmd[i + 1])
			{
				tmp = shell->input;
				shell->input = ft_strjoin(tmp, " ");
				free(tmp);
			}
		}
		free_arr_and_null(&shell->parsed_cmd);
	}
}
