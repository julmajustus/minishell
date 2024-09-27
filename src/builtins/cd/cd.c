/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by mpellegr          #+#    #+#             */
/*   Updated: 2024/09/27 10:00:30 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cd_no_path(char **envp, char *new_old_pwd, \
		int *exit_code, char *tilde)
{
	char	*new_pwd;

	new_pwd = getenv("HOME");
	if (!new_pwd)
	{
		new_pwd = ft_strdup(tilde);
		if (!new_pwd)
		{
			write (2, "minishell: cd: HOME not set\n", 28);
			*exit_code = 1;
			free(new_old_pwd);
			return (envp);
		}
	}
	chdir(new_pwd);
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_pwd);
	free(new_old_pwd);
	return (envp);
}

char	**cd_to_old_pwd(char **envp, char *new_old_pwd, int *exit_code)
{
	char	*new_pwd;
	int		i;
	int		pwd_len;
	int		start;
	int		j;
	char *temp;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "OLDPWD", 6) != 0)
		i++;
	if (!envp[i])
		return (err_oldpwd_not_set(envp, new_old_pwd, &exit_code));
	pwd_len = ft_strlen(envp[i]);
	start = 7;
	temp = (char *)malloc(sizeof(char) * (pwd_len - start + 1));
	j = 0;
	while (envp[i][start])
		temp[j++] = envp[i][start++];
	temp[j] = '\0';
	chdir(temp);
	new_pwd = ft_strjoin("PWD=", temp);
	free(temp);
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
	char	*temp;

	len = find_new_len(path, new_old_pwd);
	j = 7;
	len -= j;
	if (!len)
		len = 1;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		temp[i++] = new_old_pwd[j++];
	temp[i] = '\0';
	chdir(temp);
	new_pwd = ft_strjoin("PWD=", temp);
	free(temp);
	envp = replace_or_create_env_line(envp, new_old_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_old_pwd);
	free(new_pwd);
	return (envp);
}

char	**cd_to_next(t_shell *shell, char *new_old_pwd, \
		char *path, int *exit_code)
{
	char	*new_pwd;
	char	*temp;

	if (chdir(path) == -1)
	{
		write (2, "minishell: cd: ", 15);
		write (2, path, ft_strlen(path));
		write (2, ": No such file or directory\n", 28);
		*exit_code = 1;
		free(new_old_pwd);
		return (shell->envp);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		temp = ft_strjoin("PWD=", new_pwd);
		free(new_pwd);
		new_pwd = temp;
	}
	shell->envp = replace_or_create_env_line(shell->envp, new_pwd);
	shell->envp = replace_or_create_env_line(shell->envp, new_old_pwd);
	free(new_old_pwd);
	free(new_pwd);
	return (shell->envp);
}

char	**ft_cd(t_shell *shell, char *path)
{
	char	*new_old_pwd;
	char	*temp;

	if (arr_len(shell->parsed_cmd) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		shell->exit_code = 1;
		return (shell->envp);
	}
	temp = getcwd(NULL, 0);
	if (!temp)
	{
		temp = getenv("PWD");
		if (!temp)
			temp = ft_strdup("somethng went wrong");
	}
	new_old_pwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	if (!path)
		return (cd_no_path(shell->envp, new_old_pwd, \
					&shell->exit_code, shell->tilde));
	else if (path[0] == '-' && !path[1])
		return (cd_to_old_pwd(shell->envp, new_old_pwd, &shell->exit_code));
	else if (!ft_strcmp(path, "..") || !ft_strcmp(path, "../"))
		return (cd_to_previus(shell->envp, new_old_pwd, path));
	else
		return (cd_to_next(shell, new_old_pwd, path, &shell->exit_code));
}
