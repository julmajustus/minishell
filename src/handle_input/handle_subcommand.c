/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subcommand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:40:44 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/14 16:59:27 by jmakkone         ###   ########.fr       */
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

static void	restore_cmds_from_stack(t_shell *shell, t_cmd_stack **stack)
{
    int	i;
   	int	j;
	
	i = 0;
	shell->tmp_chained_cmds = malloc(sizeof(char *) * (stack_len(stack) + 2));
	shell->tmp_chained_tokens = malloc(sizeof(char *) * (stack_len(stack) + 2));
	init_arr(shell->tmp_chained_cmds, stack_len(stack) + 2);
	init_arr(shell->tmp_chained_tokens, stack_len(stack) + 2);
	while (*stack)
	{
		pop_from_stack(shell, stack, &shell->tmp_chained_cmds[i], &shell->tmp_chained_tokens[i]);
		i++;
	}
	shell->chained_cmds = shell->tmp_chained_cmds;
	shell->chained_tokens = shell->tmp_chained_tokens;
	j = 0;
	while (shell->chained_cmds[j] && shell->chained_tokens[j]) 
	{
		j++;

	}
}

static void	preserve_remaining_cmds(t_shell *shell, t_cmd_stack **stack, int *i)
{
    int j;
	int push_to_bottom;

	j = *i + 1;
	if (shell->in_subcmd == 1 && shell->preserving_chained_cmds == 1)
		push_to_bottom = 1;
	else
		push_to_bottom = 0;
    while (shell->chained_cmds[j])
	{
        push_to_stack(stack, shell->chained_cmds[j], shell->chained_tokens[j - 1], push_to_bottom);
        j++;
    }
	free_arr_and_null(&shell->chained_cmds);
	free_arr_and_null(&shell->chained_tokens);
}

static void return_from_subcommand(t_shell *shell, int *i, t_cmd_stack **cmd_stack)
{
	free_arr_and_null(&shell->chained_cmds);
	free_arr_and_null(&shell->chained_tokens);
	shell->preserving_chained_cmds--;
	restore_cmds_from_stack(shell, cmd_stack);
	*i = -1;
	if (!ft_strcmp(shell->chained_tokens[0], "&&") && shell->retval == 0)
		shell->execute_next = 1;
	else if (!ft_strcmp(shell->chained_tokens[0], "||") && shell->retval == 0)
		shell->execute_next = 0;
	else if (!ft_strcmp(shell->chained_tokens[0], "&&") && shell->retval != 0)
		shell->execute_next = 0;
	else if (!ft_strcmp(shell->chained_tokens[0], "||") && shell->retval != 0)
		shell->execute_next = 1;
	free_cmd_stack(cmd_stack);
	free(shell->input);
	shell->input = NULL;
	shell->returning_subcmd = 1;
}

void handle_subcommand(t_shell *shell, int *i)
{

	parse_subcmd(shell);
	shell->in_subcmd++;
	if (shell->chained_cmds[*i + 1]) 
	{
		shell->preserving_chained_cmds++;
		preserve_remaining_cmds(shell, &shell->cmd_stack, i);
	}
	else
	{
		free_arr_and_null(&shell->chained_cmds);
		free_arr_and_null(&shell->chained_tokens);
	}
	handle_input(shell);
	shell->in_subcmd--;
	if (!shell->cmd_stack)
	{
		clean_chained_cmds(shell);
		return ;
	}
	return_from_subcommand(shell, i, &shell->cmd_stack);
}
