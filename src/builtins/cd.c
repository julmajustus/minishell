/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:41:24 by mpellegr          #+#    #+#             */
/*   Updated: 2024/08/30 15:48:49 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_cd(char **envp, char *path)
{
	char	*old_pwd;
	char	*new_pwd;
	int		i;
	size_t	pwd_len;

	i = 0;
	while (envp[i] && strncmp(envp[i], "PWD", 3) != 0)
		i++;
	pwd_len = ft_strlen(envp[i]);
	old_pwd = (char *)malloc(sizeof(char) * (pwd_len + 1));
	getcwd(old_pwd, (pwd_len + 1));
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	envp = replace_or_create_env_line(envp, old_pwd);
	free(old_pwd);
	chdir(path);
	i = 0;
	while (envp[i] && strncmp(envp[i], "PWD", 3) != 0)
		i++;
	pwd_len = ft_strlen(envp[i]);
	new_pwd = (char *)malloc(sizeof(char) * (pwd_len + 1));
	getcwd(new_pwd, (pwd_len + 1));
	new_pwd = ft_strjoin("PWD=", new_pwd);
	envp = replace_or_create_env_line(envp, new_pwd);
	free(new_pwd);
	return (envp);
}
