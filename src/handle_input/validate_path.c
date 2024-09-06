/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 19:00:46 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*is_valid_path(char *cmd, char **path_list)
{
	int		i;
	char	*add_slash;
	char	*path;

	i = 0;
	while (path_list[i])
	{
		add_slash = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	**get_paths_from_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

static char	*check_if_local(t_shell *shell, int cmd_not_found)
{
	if (access(*shell->parsed_cmd, F_OK | X_OK) == 0)
		return (ft_strdup(*shell->parsed_cmd));
	else if ((access(*shell->parsed_cmd, F_OK) == 0) && \
			(access(*shell->parsed_cmd, X_OK) != 0))
		exit_no_permission(shell);
	if (cmd_not_found)
		exit_cmd_notfound(shell);
	exit_no_file(shell);
	return (NULL);
}

char	*validate_path(t_shell *shell)
{
	char	**path_list;
	char	*valid_path;

	path_list = get_paths_from_envp(shell->envp);
	if (!path_list)
		return (check_if_local(shell, 0));
	valid_path = is_valid_path(*shell->parsed_cmd, path_list);
	free_arr(path_list);
	if (!valid_path)
		return (check_if_local(shell, 1));
	return (valid_path);
}
