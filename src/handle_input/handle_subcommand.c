/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subcommand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:40:44 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/13 03:19:40 by jmakkone         ###   ########.fr       */
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
	shell->tmp_chained_cmds = malloc(sizeof(char *) * (stack_len(stack) + 1));
	shell->tmp_chained_tokens = malloc(sizeof(char *) * (stack_len(stack) + 1));
	shell->tmp_chained_cmds[stack_len(stack)] = NULL;
	shell->tmp_chained_tokens[stack_len(stack)] = NULL;
	while (*stack)
	{
		pop_from_stack(stack, &shell->tmp_chained_cmds[i], &shell->tmp_chained_tokens[i]);
		i++;
	}
	j = 0;
//	printf("in_subcmd: %d, recursion_count: \n", shell->in_subcmd);
	while (j < i / 2)
	{
		shell->tmp_chained_cmd = shell->tmp_chained_cmds[j];
		shell->tmp_chained_token = shell->tmp_chained_tokens[j];
		shell->tmp_chained_cmds[j] = shell->tmp_chained_cmds[i - j - 1];
		shell->tmp_chained_tokens[j] = shell->tmp_chained_tokens[i - j - 1];
		shell->tmp_chained_cmds[i - j - 1] = shell->tmp_chained_cmd;
		shell->tmp_chained_tokens[i - j - 1] = shell->tmp_chained_token;
		j++;
	}	
	shell->chained_cmds = shell->tmp_chained_cmds;
	shell->chained_tokens = shell->tmp_chained_tokens;
}

static void	preserve_remaining_cmds(t_shell *shell, t_cmd_stack **stack, int *i)
{
    int j;
	int push_to_bottom;

	j = *i + 1;
//	printf("Check in_subcmd: %d\n", shell->in_subcmd);
	push_to_bottom = shell->in_subcmd;
    while (shell->chained_cmds[j])
	{
//		printf("Check elements we push: %s, %s\n", shell->chained_cmds[j], shell->chained_tokens[j -1]);
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
	shell->preserving_chained_cmds = 0;
	restore_cmds_from_stack(shell, cmd_stack);
//	*i = 0;
//	while (shell->chained_tokens[*i])
//	{
//		printf("return_from_subcommand: \n[%d]cmd: %s\n[%d]token: %s\n",*i , shell->chained_cmds[*i], *i, shell->chained_tokens[*i]);
//		*i += 1;
//	}
	*i = 0;
	
//	printf("Check shell->execute_next: %d\n", shell->execute_next);
	if (!ft_strcmp(shell->chained_tokens[0], "&&") && shell->retval == 0)
		shell->execute_next = 1;
	else if (!ft_strcmp(shell->chained_tokens[0], "||") && shell->retval != 0)
		shell->execute_next = 1;
	else
		shell->execute_next = 0;
//	printf("Returning form stack\n");
	free_cmd_stack(cmd_stack);
}

void handle_subcommand(t_shell *shell, int *i)
{

	parse_subcmd(shell);
	shell->in_subcmd++;
	if (shell->chained_cmds[*i + 1]) 
	{
		shell->preserving_chained_cmds = 1;
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
		printf("Returning from NOSTACK\n");
		clean_chained_cmds(shell);
		return ;
	}
	return_from_subcommand(shell, i, &shell->cmd_stack);
}
