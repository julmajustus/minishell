/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:34:23 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/30 14:46:07 by jmakkone         ###   ########.fr       */
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
		else if (ft_isalpha(str[i]) || str[i] == '_' || (str[i] == '+' && str[i + 1] == '='))
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

static int calculate_variable_lenght(char *str)
{
	int		len;
	
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

static int	var_exists_in_pending_exports(char **pending_exports, char *str)
{
	int		i;
	char	*var;
	
	i = -1;
	var = ft_substr(str, 0, calculate_variable_lenght(str));
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

static char	**add_to_pending_exports(char **pending_exports, \
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
	var = ft_substr(str, 0, calculate_variable_lenght(str));
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

char	**ft_export(t_shell *shell, char *str)
{
	char	**tmp;

	if (!str || !*str)
	{
		tmp = copy_env(shell->envp);
		sort_envp_alphabetically(tmp);
		sort_pending_exports_alphabetically(shell->pending_exports);
		print_sorted_exports(tmp, shell->pending_exports);
		free_arr_and_null(&tmp);
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
