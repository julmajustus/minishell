/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:34:23 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/29 21:13:11 by jmakkone         ###   ########.fr       */
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
		else if (ft_isalpha(str[i]) || str[i] == '_')
			i++;
		else
		{
			ft_putendl_fd(" not a valid identifier", 2);
			*exit_code = 1;
			return (0);
		}
		if (str[i] == '=' && str[i + 1])
			break ;
	}
	if (!ft_strchr(str, '='))
		return (0);
	return (1);
}

static int	var_exists_in_pending_exports(char **pending_exports, char *var)
{
    int		i;
    size_t	var_len;

	i = -1;
    if (ft_strchr(var, '=') != NULL)
        var_len = (size_t)(ft_strchr(var, '=') - var);
    else
        var_len = ft_strlen(var);
    while (pending_exports[++i])
    {
        if (ft_strncmp(pending_exports[i], var, var_len) == 0
            && (pending_exports[i][var_len] == '\0' \
			|| pending_exports[i][var_len] == '='))
        {
            return (1);
        }
    }
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

static void	remove_from_pending_exports(t_shell *shell, char *str)
{
    int		i;
	char	*var;
	char	**new_pending_exports;

	new_pending_exports = ft_realloc(NULL, 0, sizeof(char *));
	new_pending_exports[0] = NULL;
	shell->pending_exports_size = 0;
	i = -1;
    var = ft_substr(str, 0, (size_t)(ft_strchr(str, '=') - str));
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
	if (!is_valid_variable_name(str, &shell->exit_code))
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
    return (shell->envp);
}
