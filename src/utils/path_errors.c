#include "../../inc/minishell.h"

void	error_no_file(char *file)
{
	write(2, "pipex: ", 7);
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}

void	error_no_permission(char *str)
{
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": Permission denied\n", 20);
}

void	error_command_not_found(char *cmd)
{
	write(2, "pipex: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

void	error_is_a_directory(char *str)
{
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": Is a directory\n", 17);
}
