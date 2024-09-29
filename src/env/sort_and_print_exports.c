/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_print_exports.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:04:57 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 21:42:05 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_envp_alphabetically(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (envp[++i])
	{
		j = i;
		while (envp[++j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
		}
	}
}

void	sort_pending_exports_alphabetically(char **pending_exports)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (pending_exports[++i])
	{
		j = i;
		while (pending_exports[++j])
		{
			if (ft_strcmp(pending_exports[i], pending_exports[j]) > 0)
			{
				temp = pending_exports[i];
				pending_exports[i] = pending_exports[j];
				pending_exports[j] = temp;
			}
		}
	}
}

void	print_sorted_exports(char **envp, char **pending_exports)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		printf("declare -x %.*s\"%s\"\n", j, envp[i], envp[i] + j + 1);
	}
	i = -1;
	while (pending_exports[++i])
		printf("declare -x %s\n", pending_exports[i]);
}
