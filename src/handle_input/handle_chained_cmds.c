/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chained_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:38:55 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/13 03:14:54 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_chained_cmds(t_shell *shell)
{
	free_arr_and_null(&shell->chained_cmds);
	free_arr_and_null(&shell->chained_tokens);
}

void handle_chained_cmds(t_shell *shell)
{
    int	i;
	
	i = 0;
    while (shell->chained_cmds[i])
	{
		printf("handle_chained_cmds: \n[%d]cmd: %s\n[%d]token: %s\n",i , shell->chained_cmds[i], i, shell->chained_tokens[i]);
		printf("shell->execute_next: %d retval: %d\n", shell->execute_next, shell->retval);
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
        if (shell->chained_tokens[i] && \
			!ft_strcmp(shell->chained_tokens[i], "&&") && shell->retval != 0)
            shell->execute_next = 0;
        else if (shell->chained_tokens[i] && \
			!ft_strcmp(shell->chained_tokens[i], "||") && shell->retval == 0)
            shell->execute_next = 0;
        else
            shell->execute_next = 1;
        i++;
    }
    clean_chained_cmds(shell);
}
