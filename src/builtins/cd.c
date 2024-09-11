/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/11 11:52:00 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cd_no_path(char **envp, char *new_old_pwd, int **exit_code)
{
	char	*new_pwd;
	int		i;
	int		pwd_len;
	int		start;
	int		j;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "HOME", 4) != 0)
		i++;
	if (!envp[i])
	{
		write (2, "minishell: cd: HOME not set\n", 28);
		**exit_code = 1;
		free(new_old_pwd);
		return (envp);
	}
	pwd_len = ft_strlen(envp[i]);
	start = 5;
	new_pwd = (char *)malloc(sizeof(char) * (pwd_len - start + 1));
	j = 0;
	while (envp[i][start])
		new_pwd[j++] = envp[i][start++];
	new_pwd[j] = '\0';
	chdir(new_pwd);
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_pwd);
	free(new_old_pwd);
	return (envp);
}

char	**cd_to_old_pwd(char **envp, char *new_old_pwd, int **exit_code)
{
	char	*new_pwd;
	int		i;
	int		pwd_len;
	int		start;
	int		j;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "OLDPWD", 6) != 0)
		i++;
	if (!envp[i])
	{
		write (2, "minishell: cd: OLDPWD not set\n", 30);
		**exit_code = 1;
		free(new_old_pwd);
		return (envp);
	}
	pwd_len = ft_strlen(envp[i]);
	start = 7;
	new_pwd = (char *)malloc(sizeof(char) * (pwd_len - start + 1));
	j = 0;
	while (envp[i][start])
		new_pwd[j++] = envp[i][start++];
	new_pwd[j] = '\0';
	chdir(new_pwd);
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_pwd);
	free(new_old_pwd);
	return (envp);
}

char	**cd_to_previus(char **envp, char *new_old_pwd, char *path)
{
	char	*new_pwd;
	int		i;
	int		len;
	int		j;
	int		n_of_prev;

	i = 0;
	n_of_prev = 0;
	while (path[i])
	{
		if (path[i] == '/')
			n_of_prev++;
		i++;
	}
	if (path[ft_strlen(path) - 1] != '/')
		n_of_prev++;
	len = ft_strlen(new_old_pwd);
	while (n_of_prev--)
	{
		len--;
		i = 0;
		while (new_old_pwd[len] != '/')
			len--;
	}
	j = 7;
	len -= j;
	if (!len)
		len = 1;
	new_pwd = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
		new_pwd[i++] = new_old_pwd[j++];
	new_pwd[i] = '\0';
	chdir(new_pwd);
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_old_pwd);
	free(new_pwd);
	return (envp);
}

char	**cd_to_next(char **envp, char *new_old_pwd, char *path, int **exit_code, int **already_executed)
{
//	int		i;
	char	*new_pwd;

//	i = 0;
//	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
//		i++;
//	new_pwd = ft_strdup(envp[i]);
//	new_pwd = ft_strjoin(new_pwd, "/");
//	new_pwd = ft_strjoin(new_pwd, path);
	if (chdir(path) == -1)
	{
		write (2, "minishell: cd: ", 15);
		write (2, path, ft_strlen(path));
		write (2, ": No such file or directory\n", 28);
		**exit_code = 1;
		free(new_old_pwd);
		//free(new_pwd);
		return (envp);
	}
	new_pwd = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	free(new_old_pwd);
	free(new_pwd);
	**already_executed = 1;
	return (envp);
}

char	**ft_cd(char **envp, char *path, int *exit_code, int *already_executed)
{
	char	*new_old_pwd;
	int		i;
	size_t	pwd_len;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
		i++;
	pwd_len = ft_strlen(envp[i]);
	new_old_pwd = (char *)malloc(sizeof(char) * (pwd_len + 1));
	getcwd(new_old_pwd, (pwd_len + 1));
	new_old_pwd = ft_strjoin("OLDPWD=", new_old_pwd);
	if (!path)
		return (cd_no_path(envp, new_old_pwd, &exit_code));
	else if (path[0] == '-' && !path[1])
		return (cd_to_old_pwd(envp, new_old_pwd, &exit_code));
	else if (!ft_strcmp(path, "..") || !ft_strcmp(path, "../"))
		return (cd_to_previus(envp, new_old_pwd, path));
	else
		return (cd_to_next(envp, new_old_pwd, path, &exit_code, &already_executed));
}
