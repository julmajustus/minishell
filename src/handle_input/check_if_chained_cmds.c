/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_chained_cmds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:54:42 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/04 12:28:16 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_syntax_error(t_shell *shell, int i, char token)
{
	if (!shell->input[i + 2] || shell->input[i + 2] == token)
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

static int	check_and(t_shell *shell, int i, int single_quote, \
												int double_quote)
{
	if (shell->input[i] == '&' && shell->input[i + 1] == '&' \
		&& !single_quote && !double_quote)
	{
		if (check_if_syntax_error(shell, i, '&'))
			return (-1);
		shell->chain_count++;
	}
	return (0);
}

static int	check_or(t_shell *shell, int i, int single_quote, \
												int double_quote)
{
	if (shell->input[i] == '|' && shell->input[i + 1] == '|' \
		&& !single_quote && !double_quote)
	{
		if (check_if_syntax_error(shell, i, '|'))
			return (-1);
		shell->chain_count++;
	}
	return (0);
}

int	check_if_chained_cmds(t_shell *shell)
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	shell->chain_count = 0;
	while (shell->input[++i])
	{
		update_quote_state(shell->input[i], &single_quote, &double_quote);
		if (check_and(shell, i, single_quote, double_quote) == -1)
			return (0);
		if (check_or(shell, i, single_quote, double_quote) == -1)
			return (0);
	}
	return (shell->chain_count);
}
