/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chained_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:38:55 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 20:39:28 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_chained_cmds(t_shell *shell)
{
	if (shell->input)
		free_and_null((void *)&shell->input);
	free_arr_and_null(&shell->chained_cmds);
}

void	check_execute_next(t_shell *shell, int i)
{
	if (shell->input)
		free_and_null((void *)&shell->input);
	if (!ft_strcmp(shell->chained_cmds[i], "&&") && shell->retval != 0)
		shell->execute_next = 0;
	else if (!ft_strcmp(shell->chained_cmds[i], "||") && shell->retval == 0)
		shell->execute_next = 0;
	else
		shell->execute_next = 1;
}

void	handle_chained_cmds(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->chained_cmds[++i])
	{
		if (!ft_strcmp(shell->chained_cmds[i], "&&") || \
			!ft_strcmp(shell->chained_cmds[i], "||"))
		{
			check_execute_next(shell, i);
			continue ;
		}
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
	}
	clean_chained_cmds(shell);
}
