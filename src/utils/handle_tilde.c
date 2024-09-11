/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:37:56 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/10 12:39:24 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hande_tilde(char ***args, t_shell shell, int *exit_code)
{
	int	i;

	i = -1;
	while ((*args)[++i])
	{
		if ((*args)[i][0] == '~' && !(*args)[i][1])
		{
			if (shell.tilde == NULL)
			{
				write(2, "minishell: HOME not set\n", 24);
				*exit_code = 1;
			}
			else
			{
				free((*args)[i]);
				(*args)[i] = NULL;
				(*args)[i] = ft_strdup(shell.tilde);
			}
		}
	}
}
