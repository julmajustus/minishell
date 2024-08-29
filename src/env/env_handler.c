/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:27:02 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/29 16:52:12 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char **copy_env(char **envp)
{
    char    **copy;
    int     i;

    copy = (char **)malloc(sizeof(char *) * (arr_len(envp) + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            while (i > 0)
                free(copy[--i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

char **delete_env_line(char **copy, char *str)
{
    int i;
    int j;
    char **new_copy;

    new_copy = (char **)malloc(sizeof(char *) * (arr_len(copy)));
    if (!new_copy)
        return (NULL);
    i = 0;
    j = 0;
    while(copy[i])
    {
        if (ft_strncmp(copy[i], str, ft_strlen(str) - 1) != 0)
        {
           new_copy[j] = ft_strdup(copy[i]);
           j++;
        }
        i++;
    }
    new_copy[j] = NULL;
    i = -1;
    while (copy[++i])
        free(copy[i]);
    free(copy);
    return (new_copy);
}

char    **new_env_line(char **copy, char *str)
{
    int i;
    char **new_copy;

    i = 0;
    while (copy[i])
    i++;
    new_copy = (char **)malloc(sizeof(char *) * (i + 2));
    i = -1;
    while (copy[++i])
        new_copy[i] = ft_strdup(copy[i]);
    if (!strchr(str, '='))
        new_copy[i] = ft_strjoin(ft_strdup(str), "=");
    else
        new_copy[i] = ft_strdup(str);
    new_copy[i + 1] = NULL;
    i = -1;
    while (copy[++i])
        free(copy[i]);
    free(copy);
    return (new_copy);
}

char **replace_or_create_env_line(char **copy, char *str)
{
    int i;
    size_t len;
    int lines;

    i = 0;
    len = 0;
    lines = 0;
    while (copy[lines])
        lines++;
    while (str[len] && str[len] != '=')
        len++;
    if (len != ft_strlen(str))
    {
        while (copy[i] && ft_strncmp(copy[i], str, len) != 0)
            i++;
        if (i == lines)
            return(new_env_line(copy, str));
        else
        {
            free(copy[i]);
            copy[i] = ft_strdup(str);
            return(copy);
        }
    }
    else
        return(new_env_line(copy, str));
}
