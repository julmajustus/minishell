void prompt(char **copy_envp)
{
    char *input;
    char **arr_input;
    char *path;

    while (1)
    {
        input = readline("> ");
        if(input == NULL)
            break;
        arr_input = parse_input(input);
        path = create_path(arr_input, envp);
        execve(path, arr_input, copy_envp);
    }
}
