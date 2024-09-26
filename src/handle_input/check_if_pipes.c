/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:27:41 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 09:14:37 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_pipes(t_shell *shell)
{
	int    i;
	int single_quote;
	int double_quote;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (shell->input[++i])
	{
		if (shell->input[0] == '|')
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			shell->exit_code = 2;
			return (0);
		}
		if (shell->input[i] == '|')
			if (single_quote == 0 && double_quote == 0)
				shell->pipe_count++;
		if (shell->input[i] == '\'' && double_quote == 0 && single_quote ==  0)
			single_quote = 1;
		else if (shell->input[i] == '\"' && single_quote == 0 && double_quote == 0)
			double_quote = 1;
		else if (shell->input[i] == '\'' && single_quote == 1)
			single_quote = 0;
		else if (shell->input[i] == '\"' && double_quote == 1)
			double_quote = 0;
	}
	return (shell->pipe_count);
}

void	parse_pipes(t_shell *shell)
{
	int	i;
	int	j;
	char	**new_cmd;

	new_cmd = (char **)malloc(sizeof(char *) * (2 + shell->pipe_count));
	if (!new_cmd)
		err("malloc faild");
	init_arr(new_cmd, 2 + shell->pipe_count);
	i = -1;
	j = 0;
	while (shell->input[++i])
	{
		if (shell->input[i] == '|' && shell->input[i + 1])
		{
			i++;
			j++;
		}
		else if (shell->input[i] != '|')
			new_cmd[j] = append_char(new_cmd[j], shell->input[i]);
	}
	new_cmd[j + 1] = NULL;//mostlikely not needed
	shell->arr_input = new_cmd;
}
