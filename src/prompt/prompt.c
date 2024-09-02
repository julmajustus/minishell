#include "minishell.h"

void prompt(char **envp)
{
    char *input;
    char **arr_input;
    char *path;
    pid_t pid;
    int status;

	while (1)
	{
		input = readline("> ");
		if(input != NULL && !is_empty_str(input))
		{
			arr_input = parse_arguments(input);
			if (check_if_builtin(arr_input))
			{
				envp = exec_builtin(arr_input, envp);
				free(input);
				free_arr(arr_input);
				path = NULL;
			}
			else
				path = create_path(arr_input, envp);
			if (path)
			{
				pid = fork();
				if (pid == -1)
					exit(EXIT_FAILURE);
				if (pid == 0)
				{
					execve(path, arr_input, envp);
					exit(EXIT_FAILURE);
				}
				else
					waitpid(pid, &status, 0);
				free(input);
				free_arr(arr_input);
				free(path);
			}
		}
    }
    free_arr(envp);
}
