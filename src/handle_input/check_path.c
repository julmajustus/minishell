/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 01:48:45 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_path(char *cmd, char **env_path)
{
	int		i;
	char	*add_slash;
	char	*path;

	i = 0;
	while (env_path[i])
	{
		add_slash = ft_strjoin(env_path[i], "/");
		path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	**get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*get_path(t_shell *shell)
{
	char	**env_path;
	char	*path;

	if (access(*shell->parsed_cmd, F_OK | X_OK) == 0)
		return (ft_strdup(*shell->parsed_cmd));
	env_path = get_env_path(shell->envp);
	if (!env_path)
	{
		exit_no_file(shell);
	}
	path = check_path(*shell->parsed_cmd, env_path);
	free_arr(env_path);
	if (!path)
	{
		if (*shell->parsed_cmd[0] == '/')
			err_nofile(*shell->parsed_cmd);
		else
			err_cmd_notfound(*shell->parsed_cmd);
		free_shell_allocations(shell);
		exit (127);
	}
	return (path);
}
