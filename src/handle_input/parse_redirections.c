/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:36:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 22:11:45 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_if_valid_cmd(char *cmd, int token_len, \
							char **new_parsed_cmd, int *j)
{
	if (token_len == 0)
		new_parsed_cmd[(*j)++] = ft_strdup(cmd);
}

static int	skip_tokens(t_shell *shell, int *i, int token_len)
{
	if (token_len > 0 && shell->parsed_cmd[*i + 1] && \
		(!ft_strcmp(shell->parsed_cmd[*i], "<") || \
		!ft_strcmp(shell->parsed_cmd[*i], "<<") || \
		!ft_strcmp(shell->parsed_cmd[*i], ">") || \
		!ft_strcmp(shell->parsed_cmd[*i], ">>")))
	{
		*i += 1;
		return (1);
	}
	else if (token_len > 0 && shell->parsed_cmd[*i] && \
		(!ft_strchr(shell->parsed_cmd[*i], '>') || \
		!ft_strchr(shell->parsed_cmd[*i], '<')))
		return (1);
	return (0);
}

static void	finalize_parsed_array(t_shell *shell, char **new_parsed_cmd, int *j)
{
	new_parsed_cmd[*j] = NULL;
	free_arr_and_null(&shell->parsed_cmd);
	free_and_null((void *)&shell->redir->valid_tokens);
	shell->parsed_cmd = new_parsed_cmd;
}

void	parse_redirections(t_shell *shell)
{
	char	**new_parsed_cmd;
	int		i;
	int		j;
	int		token_len;

	i = 0;
	j = 0;
	token_len = 0;
	new_parsed_cmd = malloc(sizeof(char *) * (arr_len(shell->parsed_cmd) + 1));
	if (!new_parsed_cmd)
		err("malloc failed");
	init_arr(new_parsed_cmd, (arr_len(shell->parsed_cmd) + 1));
	shell->redir->token_count = 0;
	while (shell->parsed_cmd[i])
	{
		token_len = check_if_redir_token(shell, shell->parsed_cmd[i], \
													new_parsed_cmd, &j);
		check_if_valid_cmd(shell->parsed_cmd[i], token_len, new_parsed_cmd, &j);
		if (skip_tokens(shell, &i, token_len))
			i++;
		else
			i++;
	}
	finalize_parsed_array(shell, new_parsed_cmd, &j);
}
