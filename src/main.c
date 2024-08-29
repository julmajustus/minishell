#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char **cp_env;

    (void)argc;
    (void)argv;
    cp_env = copy_env(envp);
	prompt(cp_env);
}
