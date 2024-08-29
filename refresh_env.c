#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **copy_env(char **envp)
{
    int     lines;
    char    **copy;
    int     i;

    lines = 0;
    while (envp[lines])
        lines++;
    copy = (char **)malloc(sizeof(char *) * (lines + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < lines)
    {
        copy[i] = strdup(envp[i]);
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
    int lines;
    int i;
    char **new_copy;

    lines = 0;
    while (copy[lines])
        lines++;
    lines -= 1;
    new_copy = (char **)malloc(sizeof(char *) * (lines + 1));
    if (!new_copy)
        return (NULL);
    i = 0;
    lines = 0;
    while(copy[i])
    {
        if (strncmp(copy[i], str, strlen(str)) != 0)
        {
           new_copy[lines] = strdup(copy[i]);
           lines++;
        }
        i++;
    }
    new_copy[lines] = '\0';
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
        new_copy[i] = strdup(copy[i]);
    if (!strchr(str, '='))
    {
        new_copy[i] = (char *)malloc(sizeof(char) * (strlen(str + 2))); //we can use strjoin here
        strcpy(new_copy[i], str);
        strcat(new_copy[i], "=");
    }
    else
        new_copy[i] = strdup(str);
    new_copy[i + 1] = '\0';
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
    if (len != strlen(str))
    {
        while (copy[i] && strncmp(copy[i], str, len) != 0)
            i++;
        if (i == lines)
            return(new_env_line(copy, str));
        else
        {
            free(copy[i]);
            copy[i] = strdup(str);
            return(copy);
        }
    }
    else
        return(new_env_line(copy, str));
}

int main(int argc, char **argv, char **envp)
{
    char **copy;
    int i;

    (void)argc;
    (void)argv;
    copy = copy_env(envp);
    copy = delete_env_line(copy, "PATH");
    copy = replace_or_create_env_line(copy, "USER=toagne");
    copy = replace_or_create_env_line(copy, "NEWVAR");
    i = -1;
    while (copy[++i])
        printf("%s\n", copy[i]);
    i = -1;
    while (copy[++i])
        free(copy[i]);
    free(copy);
}

