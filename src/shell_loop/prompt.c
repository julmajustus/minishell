/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:57:58 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/16 13:59:22 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_prompt(t_shell shell)
{
	char	*str;
	char	*pwd;
	int		i;
	int		n_of_slash;

	str = ft_strdup(getenv("USER"));
	if (!str)
		str = ft_strdup("someone");
	pwd = getcwd(NULL, 0);
	i = -1;
	n_of_slash = 0;
	while (pwd[++i])
		if (pwd[i] == '/')
			n_of_slash++;
	if (n_of_slash >= 2)
	{
		pwd = ft_substr(pwd, ft_strlen(shell.tilde), ft_strlen(pwd)
				- ft_strlen(shell.tilde));
		pwd = ft_strjoin("~", pwd);
	}
	str = ft_strjoin(str, "@minishell:");
	str = ft_strjoin(str, pwd);
	str = ft_strjoin(str, "$ ");
	free(pwd);
	return (str);
}

void	prompt(t_shell *shell)
{
	char	*prompt;

	prompt = create_prompt(*shell);
	shell->input = readline(prompt);
	free(prompt);
	if (shell->input != NULL && !is_empty_str(shell->input))
	{
		add_history(shell->input);
	}
	else if (!shell->input)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
}
