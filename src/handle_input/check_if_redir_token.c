/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_redir_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:12:04 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 22:41:16 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	strip_leading(char *cmd, int cmd_len, char **new_parsed_cmd, int *j)
{
	char	*command_part;

	command_part = ft_substr(cmd, 0, cmd_len);
	new_parsed_cmd[(*j)++] = command_part;
}

static void	check_if_leading_cmds(int *i, int *cmd_len, char *cmd)
{
	*cmd_len = *i;
	*i += 1;
	if ((cmd[*i - 1] == '<' && cmd[*i] == '<') \
		|| (cmd[*i - 1] == '>' && cmd[*i] == '>'))
		*i += 1;
	while (cmd[*i] == ' ')
		*i += 1;
}

int	check_if_redir_token(t_shell *shell, char *cmd, char \
									**new_parsed_cmd, int *j)
{
	int	i;
	int	cmd_len;
	int	k;

	i = -1;
	cmd_len = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			shell->redir->token_count += 1;
			k = -1;
			while (shell->redir->valid_tokens[++k])
			{
				if (shell->redir->valid_tokens[k] == shell->redir->token_count)
				{
					check_if_leading_cmds(&i, &cmd_len, cmd);
					if (cmd_len > 0)
						strip_leading(cmd, cmd_len, new_parsed_cmd, j);
					return (i);
				}
			}
		}
	}
	return (0);
}
