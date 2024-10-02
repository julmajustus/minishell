/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:18:51 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/01 11:23:12 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user(void)
{
	char	*user;

	if (getenv("USER"))
		user = ft_strdup(getenv("USER"));
	else
		return (ft_strdup("someone"));
	return (user);
}

int	count_slashes(char *pwd)
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

char	*get_pwd(char *tilde, char *pwd)
{
	char	*result;

	result = ft_substr(pwd, ft_strlen(tilde), \
			ft_strlen(pwd) - ft_strlen(tilde));
	free(pwd);
	pwd = ft_strjoin("~", result);
	free(result);
	return (pwd);
}

char	*build_prompt(char *user, char *pwd)
{
	char	*prompt;
	char	*temp;

	prompt = ft_strjoin(user, "@minishell:");
	temp = ft_strjoin(prompt, pwd);
	free(prompt);
	free(pwd);
	return (temp);
}
