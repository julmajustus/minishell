/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_chained_cmds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:54:42 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 13:13:59 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_syntax_error(t_shell *shell, int *i, char token)
{
	if (!shell->input[*i + 2] || shell->input[*i + 2] == token)
	{
		if (token == '&')
			err_syntax("&&");
		if (token == '|')
			err_syntax("||");
		shell->exit_code = 1;
		return (1);
	}
	return (0);
}

int	check_if_chained_cmds(t_shell *shell)
{
	int	i;

	i = -1;
	shell->chain_count = 0;
	while (shell->input[++i] && !ft_strchr(shell->input, '\'') \
							&& !ft_strchr(shell->input, '\"'))
	{
		if (shell->input[i] == '&' && shell->input[i + 1] == '&')
		{
			if (check_if_syntax_error(shell, &i, '&'))
				return (0);
			shell->chain_count++;
		}
		if (shell->input[i] == '|' && shell->input[i + 1] == '|')
		{
			if (check_if_syntax_error(shell, &i, '|'))
				return (0);
			shell->chain_count++;
		}
	}
	return (shell->chain_count);
}
