/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:34:23 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 18:11:24 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_variable_name(char *str, int *exit_code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[0]) || (str[0] == '=' && !str[1]))
		{
			ft_putendl_fd(" not a valid identifier", 2);
			*exit_code = 1;
			return (0);
		}
		else if (ft_isalpha(str[i]) || str[i] == '_' || \
			(str[i] == '+' && str[i + 1] == '='))
			i++;
		else
		{
			ft_putendl_fd(" not a valid identifier", 2);
			*exit_code = 1;
			return (0);
		}
		if (str[i] == '=')
			break ;
	}
	return (1);
}

char	**ft_export(t_shell *shell, char *str)
{
	if (!str || !*str)
	{
		print_sorted_exports(shell->envp, shell->pending_exports);
		return (shell->envp);
	}
	if (is_valid_variable_name(str, &shell->exit_code))
	{
		if (!ft_strchr(str, '='))
		{
			if (!var_exists_in_pending_exports(shell->pending_exports, str))
				shell->pending_exports = add_to_pending_exports(\
				shell->pending_exports, str, &shell->pending_exports_size);
		}
		else
		{
			shell->envp = replace_or_create_env_line(shell->envp, str);
			remove_from_pending_exports(shell, str);
		}
	}
	return (shell->envp);
}
