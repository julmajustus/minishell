/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:27:41 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/27 02:19:38 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_syntax_error(int *exit_code)
{
	ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
	*exit_code = 2;
	return (0);
}

int	check_if_pipes(t_shell *shell)
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (shell->input[++i])
	{
		update_quote_state(shell->input[i], &single_quote, &double_quote);
		if (shell->input[0] == '|')
			return (pipe_syntax_error(&shell->exit_code));
		if (shell->input[i] == '|' && shell->input[i - 1] == '<' && \
									!single_quote && !double_quote)
			return (pipe_syntax_error(&shell->exit_code));
		if (shell->input[i] == '|' && !single_quote && !double_quote)
				shell->pipe_count++;
	}
	return (shell->pipe_count);
}

static void	parse_cmd(t_shell *shell, int i, int start)
{
	char *cmd;

	cmd = ft_substr(shell->input, start, i - start);
	append_array(cmd, &shell->piped_cmds, &shell->pipe_count);
	free_and_null((void *)&cmd);
}

void	parse_piped_cmds(t_shell *shell)
{
	int	i;
	int	single_quote;
	int	double_quote;
	int	start;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	start = 0;
	shell->piped_cmds = NULL;
	shell->pipe_count = 0;
	while (shell->input[++i])
	{
		update_quote_state(shell->input[i], &single_quote, &double_quote);
		if (shell->input[i] == '|' && !single_quote && !double_quote)
		{
			if (i > start)
				parse_cmd(shell, i, start);
			start = i + 1;
		}
	}
	if (i > start)
		parse_cmd(shell, i, start);
}
