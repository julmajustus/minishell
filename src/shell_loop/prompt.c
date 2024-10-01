/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:57:58 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/01 11:23:20 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_prompt(t_shell *shell)
{
	char	*str;
	char	*pwd;
	int		n_of_slash;

	str = get_user();
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("somewhere");
	n_of_slash = count_slashes(pwd);
	if (n_of_slash >= 2)
		pwd = get_pwd(shell->tilde, pwd);
	shell->prompt = build_prompt(str, pwd);
	free(str);
	str = ft_strjoin(shell->prompt, "$ ");
	free(shell->prompt);
	shell->prompt = str;
}

void	prompt(t_shell *shell)
{
	create_prompt(shell);
	shell->input = readline(shell->prompt);
	if (shell->input != NULL && !is_empty_str(shell->input))
	{
		add_history(shell->input);
	}
	else if (!shell->input)
	{
		ft_putendl_fd("exit", 1);
		free_shell_allocations(shell);
		exit(shell->retval);
	}
}
