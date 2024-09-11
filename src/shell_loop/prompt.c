#include "minishell.h"

char	*create_prompt(t_shell shell)
{
	char	*str;
	char	*user;
	char	*pwd;
	int		i;
	int		j;
	int		n_of_slash;

	user = getenv("USER");
	if (!user)
		user = ft_strdup("someone");
	pwd = getenv("PWD");
	i = 0;
	while (shell.envp[i] && ft_strncmp(shell.envp[i], "PWD", 3))
		i++;
	j = -1;
	n_of_slash = 0;
	while (shell.envp[i][++j])
		if (shell.envp[i][j] == '/')
			n_of_slash++;
	if (!shell.envp[i])
		pwd = ft_strdup("somewhere");
	else if (n_of_slash < 2)
	{
		pwd = ft_strdup(shell.envp[i]);
		pwd = ft_substr(pwd, 4, ft_strlen(pwd) - 4);
	}
	else
	{
		pwd = ft_strdup(shell.envp[i]);
		pwd = ft_substr(pwd, 4 + ft_strlen(shell.tilde), ft_strlen(pwd) - 4 - ft_strlen(shell.tilde));
		pwd = ft_strjoin("~", pwd);
	}
	str = ft_strjoin(user, "@");
	str = ft_strjoin(str, "minishell:");
	str = ft_strjoin(str, pwd);
	str = ft_strjoin(str, "$ ");
	free(pwd);
	return (str);
}

void prompt(t_shell *shell)
{
	char *prompt;

	prompt = create_prompt(*shell);
	shell->input = readline(prompt);
	free(prompt);
	if(shell->input != NULL && !is_empty_str(shell->input))
	{
		add_history(shell->input);
	}
	else if (!shell->input)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
}
