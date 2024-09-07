/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:02:53 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/07 23:52:21 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc(char *limiter, int *fd)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		err("pipe");
	ft_putstr_fd("here_doc > ", 1);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd("here_doc > ", 1);
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(pipe_fd[1]);
	*fd = pipe_fd[0];
}

void	handle_redirections(t_redir *redir)
{
	int fd;

	if (redir->input_file && !redir->here_doc)
	{
		fd = open(redir->input_file, O_RDONLY);
		if (fd == -1)
			err("open input file");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (redir->here_doc)
	{
		here_doc(redir->here_doc_eof, &fd);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (redir->output_file)
	{
		if (redir->append_mode)
			fd = open(redir->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd == -1)
			err("open output file");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
