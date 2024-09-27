/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:57:58 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/27 16:24:25 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static char	*create_prompt(t_shell shell)
//{
//	char	*str;
//	char	*pwd;
//	int		i;
//	int		n_of_slash;
//
//	str = ft_strdup(getenv("USER"));
//	if (!str)
//		str = ft_strdup("someone");
//	pwd = getcwd(NULL, 0);
//	i = -1;
//	n_of_slash = 0;
//	while (pwd[++i])
//		if (pwd[i] == '/')
//			n_of_slash++;
//	if (n_of_slash >= 2)
//	{
//		pwd = ft_substr(pwd, ft_strlen(shell.tilde), ft_strlen(pwd)
//				- ft_strlen(shell.tilde));
//		pwd = ft_strjoin("~", pwd);
//	}
//	str = ft_strjoin(str, "@minishell:");
//	str = ft_strjoin(str, pwd);
//	str = ft_strjoin(str, "$ ");
//	free(pwd);
//	return (str);
//}

static char	*get_user(void)
{
    char *user;

	user = ft_strdup(getenv("USER"));
    if (!user)
        return (ft_strdup("someone"));
    return (user);
}

static int	count_slashes(char *pwd)
{
    int	n_of_slash;
    int	i;

	n_of_slash = 0;
	i = -1;
    while (pwd[++i])
        if (pwd[i] == '/')
            n_of_slash++;
    return (n_of_slash);
}

static char	*get_pwd(char *tilde, char *pwd)
{
    char	*result;

    result = ft_substr(pwd, ft_strlen(tilde), ft_strlen(pwd) - ft_strlen(tilde));
    free(pwd);
    pwd = ft_strjoin("~", result);
    free(result);
    return (pwd);
}

static char	*build_prompt(char *user, char *pwd)
{
    char	*prompt;
    char	*temp;

    prompt = ft_strjoin(user, "@minishell:");
    temp = ft_strjoin(prompt, pwd);
    free(prompt);
    free(pwd);
    return (temp);
}

static void	create_prompt(t_shell *shell)
{
    char	*str;
    char	*pwd;
    int		n_of_slash;

    str = get_user();
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        free(str);
        return ;
    }
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
// 	char	*prompt;

	create_prompt(shell);
	shell->input = readline(shell->prompt);
/*	if (isatty(fileno(stdin)))
		shell->input = readline(shell->prompt);
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		shell->input = ft_strtrim(line, "\n");
		free(line);
	}*/
//	free(shell->prompt);
	if (shell->input != NULL && !is_empty_str(shell->input))
	{
		add_history(shell->input);
	}
	else if (!shell->input)
	{
		ft_putendl_fd("exit", 1);
        free_shell_allocations(shell);
		exit(EXIT_SUCCESS);
	}
}
