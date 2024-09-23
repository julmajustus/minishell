/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:44:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 00:09:13 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_redir(t_shell *shell, int (*to_do)[30])
{
	int    i;
	int single_quote;
	int double_quote;
	int	do_count;
	int	n;

	single_quote = 0;
	double_quote = 0;
	do_count = 0;
	n = 0;
	i = -1;
	while (shell->input[++i])
	{
		if (shell->input[i] == '>' || shell->input[i] == '<')
		{
			n++;
			if (single_quote == 0 && double_quote == 0)
				(*to_do)[do_count++] = n;
		}
		if (shell->input[i] == '\'' && double_quote == 0 && single_quote ==  0)
			single_quote = 1;
		else if (shell->input[i] == '\"' && single_quote == 0 && double_quote == 0)
			double_quote = 1;
		else if (shell->input[i] == '\'' && single_quote == 1)
			single_quote = 0;
		else if (shell->input[i] == '\"' && double_quote == 1)
			double_quote = 0;
	}
	if (to_do[0])
		return (1);
	return (0);
}

void validate_redirections(t_shell *shell)
{	
	char *cmd;
	int i;
	int j;
	int	to_do[30];
	int counter;
	int	a;

	counter = 0;
	ft_bzero(to_do, sizeof(to_do));
	if (check_if_redir(shell, &to_do))
	{
		i = 0;
		while (shell->parsed_cmd[i])
		{
			cmd = shell->parsed_cmd[i];
			j = 0;
			while (cmd[j])
			{
				if (cmd[j] == '<')
				{
					counter++;
					a = -1;
					while (to_do[++a])
						if (counter == to_do[a])
							validate_input_redir(shell, &shell->parsed_cmd[i], &cmd[j], &j);
				}
				else if (cmd[j] == '>')
				{
					counter++;
					a = -1;
					while (to_do[++a])
						if (counter == to_do[a])
							validate_output_redir(shell, &shell->parsed_cmd[i], &cmd[j], &j);
				}
				j++;
			}
			i++;
		}
		if (shell->redir->input_file || shell->redir->output_file)
			parse_redirections(shell, to_do);
	}
}
