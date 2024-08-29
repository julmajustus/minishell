#include "minishell.h"

void prompt(char **copy_envp)
{
    char *input;
    char **arr_input;
    char *path;
    pid_t pid;
    int status;

    while (1)
    {
        input = readline("> ");
        if(input == NULL)
            break;
        arr_input = parse_input(input);
        path = create_path(arr_input, copy_envp);
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
        if (pid == 0)
        {
            execve(path, arr_input, copy_envp);
            exit(EXIT_FAILURE);
        }
        else
            waitpid(pid, &status, 0);
        free(input);
        free_arr(arr_input);
        free(path);
    }
    free_arr(copy_envp);
}
