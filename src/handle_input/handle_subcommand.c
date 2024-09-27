/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subcommand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:40:44 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 20:44:11 by jmakkone         ###   ########.fr       */
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
	free_and_null((void *)&shell->input);
	shell->input = sub_cmd;
}

static void	restore_cmds_from_stack(t_shell *shell, t_cmd_stack **stack)
{
	int	i;

	i = 0;
	shell->tmp_chained_cmds = malloc(sizeof(char *) * (stack_len(stack) + 1));
	init_arr(shell->tmp_chained_cmds, stack_len(stack) + 1);
	while (*stack)
	{
		pop_from_stack(shell, stack, &shell->tmp_chained_cmds[i]);
		i++;
	}
	shell->chained_cmds = shell->tmp_chained_cmds;
}

static void	preserve_remaining_cmds(t_shell *shell, t_cmd_stack **stack, int *i)
{
	int j;

	j = arr_len(shell->chained_cmds);
	while (j-- > *i + 1)
		push_to_stack(stack, shell->chained_cmds[j]);
	free_arr_and_null(&shell->chained_cmds);
}

static void return_from_subcommand(t_shell *shell, int *i, t_cmd_stack **cmd_stack)
{
	free_arr_and_null(&shell->chained_cmds);
	shell->preserving_chained_cmds--;
	restore_cmds_from_stack(shell, cmd_stack);
	*i = -1;
	free_cmd_stack(cmd_stack);
	free_and_null((void *)&shell->input);
}

void handle_subcommand(t_shell *shell, int *i)
{

	parse_subcmd(shell);
	if (shell->chained_cmds[*i + 1]) 
	{
		shell->preserving_chained_cmds++;
		preserve_remaining_cmds(shell, &shell->cmd_stack, i);
	}
	else
		free_arr_and_null(&shell->chained_cmds);
	handle_input(shell);
	if (!shell->cmd_stack)
	{
		clean_chained_cmds(shell);
		return ;
	}
	return_from_subcommand(shell, i, &shell->cmd_stack);
}
