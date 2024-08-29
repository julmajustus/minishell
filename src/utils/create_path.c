#include "../../inc/minishell.h"

static void	check_permission_path(char *path, char **cmd, char **env_paths)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
//		error_no_permission(path); add print error
		free(path);
		free_arr(env_paths);
		free_arr(cmd);
		exit(126);
	}
}

static void	path_not_found(char **env_paths, char **cmd)
{
	free_arr(env_paths);
	if (*cmd[0] == '/')
		error_no_file(*cmd);
	else if (access(*cmd, F_OK) == 0 && access(*cmd, X_OK) != 0)
	{
		error_no_permission(*cmd);
		free_arr(cmd);
		exit(126);
	}
	else
		error_command_not_found(*cmd);
	free_arr(cmd);
	exit(127);
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

static char	**find_path(char **envp, char **cmd)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
	{
		error_no_file(*cmd);
		free_arr(cmd);
		exit(127);
	}
	return (ft_split(envp[i] + 5, ':'));
}

char	*create_path(char **cmd, char **envp)
{
	int		i;
	char	**env_paths;
	char	*path;

	if (access(*cmd, F_OK) == 0 && access(*cmd, X_OK) == 0
		&& open(*cmd, O_DIRECTORY) == -1)
		return (ft_strdup(*cmd));
	env_paths = find_path(envp, cmd);
	i = 0;
	while (env_paths[i])
	{
		path = add_cmd_to_path(env_paths[i], *cmd);
		if ((access(path, F_OK) == 0 && access(path, X_OK) == 0)
			&& open(*cmd, O_DIRECTORY) == -1)
		{
			free_arr(env_paths);
			return (path);
		}
		check_permission_path(path, cmd, env_paths);
		free(path);
		i++;
	}
	path_not_found(env_paths, cmd);
	return (NULL);
}

