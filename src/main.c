#include "minishell.h"
/*
void    handle_siginit(int sig)
{
    (void)sig;
    write(1, "\n", 3);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
*/
int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

    (void)argc;
    (void)argv;
    shell.envp = copy_env(envp);
//    signal(SIGINT, handle_siginit);
	shell_loop(&shell);
	return (0);
}
