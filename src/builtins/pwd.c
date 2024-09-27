/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:06:00 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/27 03:39:11 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **envp)
{
	char	*pwd;

	if (!envp || !(*envp))
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = getenv("PWD");
		if (!pwd)
			ft_putendl_fd("pwd not found", 2);
	}
	printf("%s\n", pwd);
	free(pwd);
}
