#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

    (void)argc;
    (void)argv;
    shell.envp = copy_env(envp);
	shell_loop(&shell);
	return (0);
}
