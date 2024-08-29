

int main(int argc, char **argv, char **envp)
{
    char **copy;
    int i;

    (void)argc;
    (void)argv;
    copy = copy_env(envp);
    copy = delete_env_line(copy, "PATH");
    copy = replace_or_create_env_line(copy, "USER=toagne");
    copy = replace_or_create_env_line(copy, "NEWVAR=sflgbn");
    i = -1;
    while (copy[++i])
        printf("%s\n", copy[i]);
}

