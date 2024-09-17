/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_chained_cmds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:54:42 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/16 15:01:13 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_chained_cmds(t_shell *shell)
{
	int	i;

	i = -1;
	shell->chain_count = 0;
	while(shell->input[++i] && !ft_strchr(shell->input, '\'') && !ft_strchr(shell->input, '\"'))
	{
		if (shell->input[i] == '&' && shell->input[i + 1] == '&')
		{
			if(!shell->input[i + 2] || shell->input[i + 2] == '&')
			{
				err_syntax("&&");
				return (0);
			}
			shell->chain_count++;
		}
		if (shell->input[i] == '|' && shell->input[i + 1] == '|')
		{
			if(!shell->input[i + 2] || shell->input[i + 2] == '|')
			{
				err_syntax("||");
				return (0);
			}
			shell->chain_count++;
		}
	}
	return (shell->chain_count);
}
