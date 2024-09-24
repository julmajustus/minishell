/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:44:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 01:54:59 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_valid_token_arr(t_shell *shell, int *n)
{
	shell->redir->valid_tokens = ft_realloc(shell->redir->valid_tokens, \
							 sizeof(int) * shell->redir->token_count, \
							 sizeof(int) * (shell->redir->token_count + 1));
	if (!shell->redir->valid_tokens)
		err("Realloc failed");
	shell->redir->valid_tokens[shell->redir->token_count] = *n;
	shell->redir->token_count++;
}

int check_if_redir(t_shell *shell)
{
	int i;
	int single_quote;
	int double_quote;
	int n;

	single_quote = 0;
	double_quote = 0;
	n = 0;
	i = -1;
	while (shell->input[++i])
	{
		update_quote_state(shell->input[i], &single_quote, &double_quote);
		if (shell->input[i] == '>' || shell->input[i] == '<')
		{
			n++;
			if (single_quote == 0 && double_quote == 0)
				append_valid_token_arr(shell, &n);
		}
	}
	return (shell->redir->token_count);
}

static void	validate_redirection_token(t_shell *shell, int *i, char *token, int *token_idx)
{
	int	k;

	k = -1;
	while (++k < shell->redir->token_count)
	{
		if (shell->redir->token_counter == shell->redir->valid_tokens[k])
		{
			if (*token == '<')
				validate_input_redir(shell, &shell->parsed_cmd[*i], token, token_idx);
			else if (*token == '>')
				validate_output_redir(shell, &shell->parsed_cmd[*i], token, token_idx);
		}
	}
}

static void	parse_input_str(t_shell *shell, int *i)
{
	char	*cmd;
	int		j;

	cmd = shell->parsed_cmd[*i];
	j = -1;
	while (cmd[++j])
	{
		if (cmd[j] == '<' || cmd[j] == '>')
		{
			shell->redir->token_counter += 1;
			validate_redirection_token(shell, i, &cmd[j], &j);
		}
	}
}

void	validate_redirections(t_shell *shell)
{	
	int	i;

	if (check_if_redir(shell))
	{
		i = -1;
		while (shell->parsed_cmd[++i])
			parse_input_str(shell, &i);
		if (shell->redir->input_file || shell->redir->output_file)
			parse_redirections(shell);
	}
}
