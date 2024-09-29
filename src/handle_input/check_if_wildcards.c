/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:49:34 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 22:34:10 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_array(t_shell *shell, int *token_count)
{
	int	i;
	int	start;
	int	single_quote;
	int	double_quote;

	i = -1;
	start = 0;
	single_quote = 0;
	double_quote = 0;
	while (shell->input[++i])
	{
		update_quote_state(shell->input[i], &single_quote, &double_quote);
		if (ft_isspace(shell->input[i]) && !single_quote && !double_quote)
		{
			if (i > start)
			{
				shell->input[i] = '\0';
				append_array(&shell->input[start], &shell->parsed_cmd, \
															token_count);
			}
			start = i + 1;
		}
	}
	if (i > start)
		append_array(&shell->input[start], &shell->parsed_cmd, token_count);
}

static void	create_string(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = -1;
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
}

void	check_if_wildcards(t_shell *shell)
{
	int		token_count;

	token_count = 0;
	if (ft_strchr(shell->input, '*'))
	{
		create_array(shell, &token_count);
		handle_wildcards(shell);
		create_string(shell);
		free_arr_and_null(&shell->parsed_cmd);
	}
}
