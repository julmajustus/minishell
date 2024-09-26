/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 12:15:44 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
		if (access(path, F_OK) == 0)
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
	if (access(valid_path, X_OK) != 0)
	{
		free(valid_path);
		exit_no_permission(shell);
	}
	return (valid_path);
}
*/

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
