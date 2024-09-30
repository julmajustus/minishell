/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pending_exports.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:09:49 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 18:10:47 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_var_name_length(char *str)
{
	int	len;

	len = -1;
	while (str[++len])
	{
		if (str[len] == '+' && str[len + 1] == '=')
			break ;
		if (str[len] == '=')
			break ;
	}
	return (len);
}

int	var_exists_in_pending_exports(char **pending_exports, char *str)
{
	int		i;
	char	*var;

	i = -1;
	var = ft_substr(str, 0, env_var_name_length(str));
	while (pending_exports[++i])
	{
		if (!ft_strcmp(pending_exports[i], var))
		{
			free(var);
			return (1);
		}
	}
	free(var);
	return (0);
}

char	**add_to_pending_exports(char **pending_exports, \
							char *str, int *pending_exports_size)
{
	int	i;

	i = -1;
	while (pending_exports[++i])
	{
		if (ft_strncmp(pending_exports[i], str, ft_strlen(str)) == 0)
			return (pending_exports);
	}
	append_array(str, &pending_exports, pending_exports_size);
	return (pending_exports);
}

void	remove_from_pending_exports(t_shell *shell, char *str)
{
	int		i;
	char	*var;
	char	**new_pending_exports;

	new_pending_exports = ft_realloc(NULL, 0, sizeof(char *));
	new_pending_exports[0] = NULL;
	shell->pending_exports_size = 0;
	i = -1;
	var = ft_substr(str, 0, env_var_name_length(str));
	while (shell->pending_exports[++i])
	{
		if (ft_strcmp(shell->pending_exports[i], var))
			append_array(shell->pending_exports[i], \
				&new_pending_exports, &shell->pending_exports_size);
	}
	free(var);
	free_arr_and_null(&shell->pending_exports);
	shell->pending_exports = new_pending_exports;
}
