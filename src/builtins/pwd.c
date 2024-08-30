/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:06:00 by mpellegr          #+#    #+#             */
/*   Updated: 2024/08/30 10:36:25 by mpellegr         ###   ########.fr       */
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
	char pwd[1024]; // it seems that even if you unset PWD if you run PWD it still finds the path so maybe this solution is better

	if (!envp || !(*envp))
		return ;
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}
/*
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	pwd(envp);
}
*/
