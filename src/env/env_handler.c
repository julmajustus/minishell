/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:27:02 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 18:14:26 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <unistd.h>

char **copy_env(char **envp)
{
    char    **new_envp;
    int     i;

    new_envp = (char **)malloc(sizeof(char *) * (arr_len(envp) + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        if (!new_envp[i])
        {
            while (i > 0)
                free(new_envp[--i]);
            free(new_envp);
            return (NULL);
        }
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}

char **delete_env_line(char **envp, char *str)
{
    int i;
    int j;
    char **new_envp;

    new_envp = (char **)malloc(sizeof(char *) * arr_len(envp));
    if (!new_envp)
        return (NULL);
    i = 0;
    j = 0;
    while(envp[i])
    {
        if (ft_strncmp(envp[i], str, ft_strlen(str)))
        {
           new_envp[j] = ft_strdup(envp[i]);
           j++;
        }
        i++;
    }
    new_envp[j] = NULL;
	free_arr(envp);
    return (new_envp);
}

static char **modify_existing(char **envp, char *str, size_t arg_len)
{
    int		i;
	char 	*old_arg;
	char 	*new_arg;

    i = -1;
    while (envp[++i])
	{
        if (!ft_strncmp(envp[i], str, arg_len) 
			&& (envp[i][arg_len] == '=' || envp[i][arg_len + 1] == '='))
			break ;
	}
	if (str[arg_len] == '+' && str[arg_len + 1] == '=')
	{
		old_arg = ft_strdup(envp[i]);
		new_arg = ft_substr(str, arg_len + 2, ft_strlen(str));
		free(envp[i]);
		envp[i] = ft_strjoin(old_arg, new_arg);
		free(old_arg);
		free(new_arg);
	}
	else
	{
		free(envp[i]);
		envp[i] = ft_strdup(str);
	}
	return(envp);
}

static	char **add_new_line(char **envp, char *str)
{
    int		i;

    char	**new_envp;
	new_envp = (char **)malloc((sizeof(char *) * arr_len(envp)) + 2);
	i = -1;
	while (envp[++i])
		new_envp[i] = ft_strdup(envp[i]);
	new_envp[i] = ft_strdup(str);
	new_envp[i + 1] = NULL;
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
	return (new_envp);

}

char **replace_or_create_env_line(char **envp, char *str)
{
    int		i;
    size_t	arg_len;

	if (!ft_strchr(str, '='))
		return (envp);
    arg_len = 0;
    while (str[arg_len] && str[arg_len] != '+' && str[arg_len] != '=')
		arg_len++;
    i = -1;
    while (envp[++i])
	{
        if (!ft_strncmp(envp[i], str, arg_len) 
			&& (envp[i][arg_len] == '=' || envp[i][arg_len + 1] == '='))
			return (modify_existing(envp, str, arg_len));
	}
	return (add_new_line(envp, str));
}
