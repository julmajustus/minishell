/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:06:00 by mpellegr          #+#    #+#             */
/*   Updated: 2024/10/01 09:43:08 by mpellegr         ###   ########.fr       */
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
		ft_putendl_fd("pwd not found", 2);
		pwd = ft_strdup("somewhere");
	}
	printf("%s\n", pwd);
	free(pwd);
}
