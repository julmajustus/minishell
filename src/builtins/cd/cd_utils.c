/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:50:41 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/26 11:54:19 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**err_oldpwd_not_set(char **envp, char *new_old_pwd, int **exit_code)
{
	write (2, "minishell: cd: OLDPWD not set\n", 30);
	**exit_code = 1;
	free(new_old_pwd);
	return (envp);
}

int	find_new_len(char *path, char *new_old_pwd)
{
	int	i;
	int	n_of_prev;
	int	len;

	i = -1;
	n_of_prev = 0;
	while (path[++i])
		if (path[i] == '/')
			n_of_prev++;
	if (path[ft_strlen(path) - 1] != '/')
		n_of_prev++;
	len = ft_strlen(new_old_pwd);
	while (n_of_prev--)
	{
		len--;
		while (new_old_pwd[len] != '/')
			len--;
	}
	return (len);
}
