/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:36:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/07 22:16:23 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void strip_leading(char *cmd, int cmd_len, char **new_parsed_cmd, int *j)
{
    char *command_part;

    command_part = ft_substr(cmd, 0, cmd_len);
    new_parsed_cmd[(*j)++] = command_part;
}

static int parse_tokens(char *cmd, char **new_parsed_cmd, int *j)
{
    int i;
    int cmd_len;

    i = 0;
    cmd_len = 0;
    while (cmd[i])
    {
        if (cmd[i] == '<' || cmd[i] == '>')
        {
            cmd_len = i;
            i++;
            if ((cmd[i - 1] == '<' && cmd[i] == '<') \
				|| (cmd[i - 1] == '>' && cmd[i] == '>'))
                i++;
            while (cmd[i] == ' ')
                i++;
            if (cmd_len > 0)
                strip_leading(cmd, cmd_len, new_parsed_cmd, j);
            return i;
        }
        i++;
    }
    return 0;
}

static void skip_valid(char *cmd, int token_len, char **new_parsed_cmd, int *j)
{
    if (token_len == 0)
    {
        new_parsed_cmd[(*j)++] = ft_strdup(cmd);
    }
}

void parse_redirections(t_shell *shell)
{
    char **new_parsed_cmd;
    int i;
	int	j;
	int	token_len;
	
	i = 0;
	j = 0;
	token_len = 0;
    new_parsed_cmd = malloc(sizeof(char *) * (arr_len(shell->parsed_cmd) + 1));
    if (!new_parsed_cmd)
        err("malloc failed");
    init_arr(new_parsed_cmd, (arr_len(shell->parsed_cmd) + 1));
    while (shell->parsed_cmd[i])
    {
        token_len = parse_tokens(shell->parsed_cmd[i], new_parsed_cmd, &j);
        skip_valid(shell->parsed_cmd[i], token_len, new_parsed_cmd, &j);
        if (token_len > 0 && shell->parsed_cmd[i + 1])
            i++;
        i++;
    }
    new_parsed_cmd[j] = NULL;
    free_arr(shell->parsed_cmd);
    shell->parsed_cmd = new_parsed_cmd;
}
