/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:06:00 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/26 00:53:32 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <string.h>
#include <unistd.h>
#include <stdio.h>
*/

#include "minishell.h"

void	ft_pwd(char **envp)
{
/*	int i;
	int j;

	if (!envp || !*envp)
		return ;
	i = 0;
	while (envp[i] && strncmp(envp[i], "PWD", 3) != 0)
		i++;
	j = 0;
	while (envp[i][j] && envp[i][j] != '=')
		j++;
	j++;
	while (envp[i][j])
	{
		write(1, &envp[i][j], 1);
		j++;
	}
	write(1, "\n", 1);*/
	char	*pwd; // it seems that even if you unset PWD if you run PWD it still finds the path so maybe this solution is better
	int		i;
	size_t	pwd_len;

	if (!envp || !(*envp))
		return ;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
		i++;
	pwd_len = ft_strlen(envp[i]);
	pwd = (char *)malloc(sizeof(char) * (pwd_len + 1));
	getcwd(pwd, (pwd_len + 1));
	printf("%s\n", pwd);
	free(pwd);
}
/*
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	pwd(envp);
}
*/
