/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:27:02 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/29 15:17:56 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <string.h>

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

    new_copy = (char **)malloc(sizeof(char *) * arr_len(copy));
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

char **replace_or_create_env_line(char **copy, char *str)
{
    int i;
    size_t len;
    char **new_copy;

    i = 0;
    len = 0;
    while (str[len] && str[len] != '=')
        len++;
    if (len == ft_strlen(str))
    {
        while (copy[i])
            i++;
        new_copy = (char **)malloc(sizeof(char *) * (i + 2));
        i = -1;
        while (copy[++i])
            new_copy[i] = ft_strdup(copy[i]);
        new_copy[i] = (char *)malloc(sizeof(char) * (ft_strlen(str + 2))); //we can use strjoin here
        strcpy(new_copy[i], str);
        strcat(new_copy[i], "=");
        new_copy[i + 1] = NULL;
        i = -1;
        while (copy[++i])
            free(copy[i]);
        free(copy);
        return (new_copy);
    }
    else
    {
        while (copy[i] && ft_strncmp(copy[i], str, len) != 0)
            i++;
        free(copy[i]);
        copy[i] = ft_strdup(str);
        return(copy);
    }
}
