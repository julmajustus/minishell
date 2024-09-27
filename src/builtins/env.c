/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:03:00 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/27 10:18:06 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env(char **envp, char **parsed_cmd, int *extit_code)
{
	int	i;

	if (arr_len(parsed_cmd) > 1)
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(parsed_cmd[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		*extit_code = 127;
		return (envp);
	}
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (envp);
}
