/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:23:26 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/27 02:51:26 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc(char *limiter, int *fd)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		err("pipe");
	ft_putstr_fd("> ", 1);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(pipe_fd[1]);
	*fd = pipe_fd[0];
}

void	handle_here_doc(t_shell *shell)
{
	int	i;
	int	fd;

	if (shell->redir->here_doc && shell->redir->here_doc_eof)
	{
		i = -1;
		while (shell->redir->here_doc_eof[++i])
			here_doc(shell->redir->here_doc_eof[i], &fd);
		dup2(fd, STDIN_FILENO);
		close(fd);
		shell->redir->here_doc = 0;
	}
}
