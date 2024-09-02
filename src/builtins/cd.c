/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/* By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:41:24 by mpellegr          #+#    #+#             */
/*   Updated: 2024/08/30 15:59:19 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cd_no_path(char **envp, char *new_old_pwd)
{
	char	*new_pwd;
	int		i;
	int		pwd_len;
	int		start;
	int		j;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "HOME", 4) != 0)
		i++;
	pwd_len = ft_strlen(envp[i]);
	start = 5;
	new_pwd = (char *)malloc(sizeof(char) * (pwd_len - start + 1));
	j = 0;
	while(envp[i][start])
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
	while(envp[i] && ft_strncmp(envp[i], "OLDPWD", 6) != 0)
		i++;
	pwd_len = ft_strlen(envp[i]);
	start = 7;
	new_pwd = (char *)malloc(sizeof(char) * (pwd_len - start + 1));
	j = 0;
	while(envp[i][start])
		new_pwd[j++] = envp[i][start++];
	new_pwd[j] = '\0';
	chdir(new_pwd);
	printf("%s\n", new_pwd);
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_pwd);
	free(new_old_pwd);
	return (envp);
}

char	**cd_to_previus(char **envp, char *new_old_pwd)
{
	char	*new_pwd;
	int		i;
	int		len;
	int		j;

	i = 0;
	len = ft_strlen(new_old_pwd);
	while (new_old_pwd[len] != '/')
		len--;
	j = 7;
	new_pwd = (char *)malloc(sizeof(char) * (len - j + 1));
	while (i < len - j)
	{
		new_pwd[i] = new_old_pwd[j];
		i++;
		j++;
	}
	new_pwd[i] = '\0';
	chdir(new_pwd);
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_old_pwd);
	free(new_pwd);
	return (envp);
}

char	**ft_cd(char **envp, char *path)
{
	char	*new_old_pwd;
	char	*new_pwd;
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
		return (cd_no_path(envp, new_old_pwd));
	else if (path[0] == '-')
		return (cd_to_old_pwd(envp, new_old_pwd));
	else if (path[0] == '.' && path[1] == '.')
		return (cd_to_previus(envp, new_old_pwd));
	envp = replace_or_create_env_line(envp, new_old_pwd);
	free(new_old_pwd);
	chdir(path);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
		i++;
	pwd_len = ft_strlen(envp[i]);
	new_pwd = (char *)malloc(sizeof(char) * (pwd_len + 1));
	getcwd(new_pwd, (pwd_len + 1));
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_pwd);
	return (envp);
}
