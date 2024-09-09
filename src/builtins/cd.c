/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/09 17:04:11 by mpellegr         ###   ########.fr       */
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

char	**cd_to_old_pwd(char **envp, char *new_old_pwd)
{
	char	*new_pwd;
	int		i;
	int		pwd_len;
	int		start;
	int		j;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "OLDPWD", 6) != 0)
		i++;
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

char	**cd_to_next(char **envp, char *new_old_pwd, char *path)
{
	int		i;
	char	*new_pwd;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
		i++;
	new_pwd = ft_strdup(envp[i]);
	new_pwd = ft_strjoin(new_pwd, "/");
	new_pwd = ft_strjoin(new_pwd, path);
	chdir(path);
	envp = replace_or_create_env_line(envp, new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	free(new_old_pwd);
	free(new_pwd);
	return (envp);
}

char	**cd_tilde(char **envp, char *new_old_pwd, char *path)
{
	char	*path_without_tilde;
	int		i;
	int		j;
	char	*copy_new_old_pwd;

	path_without_tilde = (char *)malloc(sizeof(char) * ft_strlen(path));
	i = 2;
	j = 0;
	while (path[i])
		path_without_tilde[j++] = path[i++];
	path_without_tilde[j] = '\0';
	copy_new_old_pwd = ft_strdup(new_old_pwd);
//	envp = cd_no_path(envp, new_old_pwd);
	envp = cd_to_next(envp, copy_new_old_pwd, path_without_tilde);
	free(path_without_tilde);
	return (envp);
}

char	**ft_cd(char **envp, char *path, int *exit_code)
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
	else if (path[0] == '-')
		return (cd_to_old_pwd(envp, new_old_pwd));
	else if (path[0] == '.' && path[1] == '.' && (path[2] == '/' || !path[2]))
		return (cd_to_previus(envp, new_old_pwd, path));
	else if (path[0] == '~')
		return (cd_tilde(envp, new_old_pwd, path));
	else
		return (cd_to_next(envp, new_old_pwd, path));
}
