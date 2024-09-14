/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chained_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:38:55 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/14 17:37:23 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_chained_cmds(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	shell->input = NULL;
	free_arr_and_null(&shell->chained_cmds);
	free_arr_and_null(&shell->chained_tokens);
}

static void check_execute_next_after_subcmd(t_shell *shell, int i)
{
	if (shell->input)
		free(shell->input);
	shell->input = NULL;
	if (!shell->chained_tokens[i + 1])
		return ;
	if (!ft_strcmp(shell->chained_tokens[i + 1], "&&") && shell->retval == 0)
		shell->execute_next = 1;
	else if (!ft_strcmp(shell->chained_tokens[i + 1], "||") && shell->retval == 0)
		shell->execute_next = 0;
	else if (!ft_strcmp(shell->chained_tokens[i + 1], "&&") && shell->retval != 0)
		shell->execute_next = 0;
	else if (!ft_strcmp(shell->chained_tokens[i + 1], "||") && shell->retval != 0)
		shell->execute_next = 1;
}

void check_execute_next(t_shell *shell, int i)
{
	if (shell->input)
		free(shell->input);
	shell->input = NULL;
	if (shell->chained_tokens[i] && \
		!ft_strcmp(shell->chained_tokens[i], "&&") && shell->retval != 0)
		shell->execute_next = 0;
	else if (shell->chained_tokens[i] && \
			!ft_strcmp(shell->chained_tokens[i], "||") && shell->retval == 0)
		shell->execute_next = 0;
	else
		shell->execute_next = 1;
}

void handle_chained_cmds(t_shell *shell)
{
    int	i;
	
	i = -1;
    while (shell->chained_cmds[++i])
	{
		shell->input = ft_strdup(shell->chained_cmds[i]);
        if (ft_strchr(shell->input, '('))
		{
            handle_subcommand(shell, &i);
			if (!shell->chained_cmds)
				return ;
            continue ;
        }
        if (shell->execute_next)
            handle_input(shell);
		if (shell->returning_subcmd)
			check_execute_next_after_subcmd(shell,  i);
		else
			check_execute_next(shell, i);
    }
    clean_chained_cmds(shell);
}
