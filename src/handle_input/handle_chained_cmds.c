/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chained_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:38:55 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/12 00:09:27 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_subcmd(t_shell *shell)
{
	int i;
	int	paren_count;
	char *sub_cmd;
	
	sub_cmd = NULL;
	i = 0;
	paren_count = 1;
	while (shell->input[i] && shell->input[i] != '(')
		i++;
	while (shell->input[++i])
	{
		if (shell->input[i] == '(')
			paren_count++;
		else if (shell->input[i] == ')')
			paren_count--;
		if (!paren_count)
			break ;
		sub_cmd = append_char(sub_cmd, shell->input[i]);	
	}
	free(shell->input);
	shell->input = sub_cmd;
}

static void	preserve_remaining_cmds(t_shell *shell, int i)
{
	int j;
	int k;

	shell->tmp_chained_cmds = malloc(sizeof(char *) * (arr_len(shell->chained_cmds) + 2));
	shell->tmp_chained_tokens = malloc(sizeof(char *) * (arr_len(shell->chained_cmds) + 2));
	init_arr(shell->tmp_chained_cmds, (arr_len(shell->chained_cmds) + 2));
	init_arr(shell->tmp_chained_tokens, (arr_len(shell->chained_cmds) + 2));
	j = i + 1;
	k = 0;
	while (shell->chained_cmds[j])
	{
		shell->tmp_chained_cmds[k] = ft_strdup(shell->chained_cmds[j]);
		if (shell->chained_tokens[j -1])
			shell->tmp_chained_tokens[k] = ft_strdup(shell->chained_tokens[j - 1]);
		j++;
		k++;
	}
	free_arr(shell->chained_cmds);
	free_arr(shell->chained_tokens);
}

static void handle_subcommand(t_shell *shell, int *i)
{
	shell->in_subcmd++;
	parse_subcmd(shell);
	if (shell->chained_cmds[*i + 1])
	{
		shell->preserving_chained_cmds = 1;
		preserve_remaining_cmds(shell, *i);
		handle_input(shell);
		free_arr(shell->chained_cmds);
		free_arr(shell->chained_tokens);
		shell->chained_cmds = shell->tmp_chained_cmds;
		shell->chained_tokens = shell->tmp_chained_tokens;
		shell->in_subcmd--;
		shell->preserving_chained_cmds = 0;
		*i = 0;
	}
	else
	{
		free_arr(shell->chained_cmds);
		free_arr(shell->chained_tokens);
		handle_input(shell);
		shell->in_subcmd--;
	}
}

static void	clean_chained_cmds(t_shell *shell)
{
	if (shell->in_subcmd || shell->preserving_chained_cmds)
		return ;
	free_arr(shell->chained_cmds);
	free_arr(shell->chained_tokens);
}

void handle_chained_cmds(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->chained_cmds[++i])
	{
		shell->input = ft_strdup(shell->chained_cmds[i]);
		if (shell->in_subcmd && !shell->execute_next)
			return ;
		if (ft_strchr(shell->input, '('))
		{
			handle_subcommand(shell, &i);
			continue;
		}
		if (shell->execute_next)
			handle_input(shell);
		if (shell->chained_tokens[i] && !ft_strcmp(shell->chained_tokens[i], "&&") && shell->retval != 0)
			shell->execute_next = 0;
		else if (shell->chained_tokens[i] && !ft_strcmp(shell->chained_tokens[i], "||") && shell->retval == 0)
			shell->execute_next = 0;
		else
			shell->execute_next = 1;
	}
	clean_chained_cmds(shell);
}
