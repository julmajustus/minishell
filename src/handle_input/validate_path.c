/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/10/01 10:05:16 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_permission_path(char *path, char **env_paths, t_shell *shell)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		free(path);
		free_arr(env_paths);
		exit_no_permission(shell);
	}
}

static char	*add_cmd_to_path(char *env_path, char *cmd)
{
	char	*temp_path;
	char	*path;

	temp_path = ft_strjoin(env_path, "/");
	path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	return (path);
}

static void	path_not_found(char **env_paths, char **cmd, t_shell *shell)
{
	free_arr(env_paths);
	if ((*cmd)[0] == '/')
		exit_no_file(shell);
	else if ((*cmd)[0] == '.' && (*cmd)[1] == '/')
	{
		if (access(*cmd, F_OK) != 0)
			exit_no_file(shell);
		if (access(*cmd, F_OK) == 0 && access(*cmd, X_OK) != 0)
			exit_no_permission(shell);
	}
	else
		exit_cmd_notfound(shell);
}

static char	**find_path(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		exit_no_file(shell);
	return (ft_split(envp[i] + 5, ':'));
}

char	*validate_path(t_shell *shell)
{
	int		i;
	char	**env_paths;
	char	*path;

	if (access(*shell->parsed_cmd, F_OK) == 0 && \
		access(*shell->parsed_cmd, X_OK) == 0 && \
		open(*shell->parsed_cmd, O_DIRECTORY) == -1)
		return (ft_strdup(*shell->parsed_cmd));
	env_paths = find_path(shell->envp, shell);
	i = 0;
	while (env_paths[i])
	{
		path = add_cmd_to_path(env_paths[i], *shell->parsed_cmd);
		if ((access(path, F_OK) == 0 && access(path, X_OK) == 0)
			&& open(*shell->parsed_cmd, O_DIRECTORY) == -1)
		{
			free_arr(env_paths);
			return (path);
		}
		check_permission_path(path, env_paths, shell);
		free(path);
		i++;
	}
	path_not_found(env_paths, shell->parsed_cmd, shell);
	return (NULL);
}
