/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:45:45 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 14:05:39 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(t_shell *shell, char *str)
{
	int	i;

	if (!str || !*str || ft_strchr(str, '='))
		return (shell->envp);
	i = -1;
	remove_from_pending_exports(shell, str);
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], str, ft_strlen(str)) == 0 && \
			shell->envp[i][ft_strlen(str)] == '=')
			return (delete_env_line(shell->envp, str));
	}
	return (shell->envp);
}
