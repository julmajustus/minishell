#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_redir redir;

    (void)argc;
    (void)argv;
	shell.redir = &redir;
	init_shell_variables(&shell);
    shell.envp = copy_env(envp);
	init_signals();
	shell_loop(&shell);
	return (0);
}
