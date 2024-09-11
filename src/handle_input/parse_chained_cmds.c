/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chained_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:15:07 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/11 15:27:25 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_subcmd(t_shell *shell, int *i, int *j)
{
	int	paren_count;

	paren_count = 0;
	while (shell->input[*i])
	{
		if (shell->input[*i] == '(')
			paren_count++;
		else if (shell->input[*i] == ')')
			paren_count--;
		if (!paren_count)
			break ;
		shell->chained_cmds[*j] = append_char(shell->chained_cmds[*j], shell->input[*i]);	
		*i += 1;
	}
}

static void	parse_tokens(t_shell *shell, int *i, int *j)
{
	int k;
	
	k = 0;
	if (shell->input[*i] == '&' && shell->input[*i + 1] == '&' && shell->input[*i + 2])
	{
		shell->chained_tokens[k++] = ft_strdup("&&");
		*i += 2;
		*j += 1;
	}
	if (shell->input[*i] == '|' && shell->input[*i + 1] == '|' && shell->input[*i + 2])
	{
		shell->chained_tokens[k++] = ft_strdup("||");
		*i += 2;
		*j += 1;
	}
}

void	parse_chained_cmds(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	shell->chained_cmds = malloc(sizeof(char *) * (shell->chain_count + 2));
	shell->chained_tokens = malloc(sizeof(char *) * (shell->chain_count + 2));
	if (!shell->chained_cmds || !shell->chained_tokens)
		err("malloc failed");
	init_arr(shell->chained_cmds, shell->chain_count + 2);
	init_arr(shell->chained_tokens, shell->chain_count + 2);
	while (shell->input[i])
	{
		if (shell->input[i] == '(')
			parse_subcmd(shell, &i, &j);
		if (shell->input[i] == '&' || shell->input[i] == '|')
			parse_tokens(shell, &i, &j);
		shell->chained_cmds[j] = append_char(shell->chained_cmds[j], shell->input[i]);	
		i++;
	}
	free(shell->input);
}
