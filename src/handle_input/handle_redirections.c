/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:02:53 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/23 14:48:15 by jmakkone         ###   ########.fr       */
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

static int	validate_inputfile_permission(t_redir *redir, int *exit_code)
{
	if (redir->input_file && !redir->here_doc)
	{
		if (access(redir->input_file, F_OK) != 0)
		{
			err_nofile(redir->input_file);
			*(exit_code) = 1;
			return (1);
		}
		if (access(redir->input_file, R_OK) != 0)
		{
			err_no_permission(redir->input_file);
			*(exit_code) = 1;
			return (1);
		}
	}
	return (0);
}

static int	validate_outputfile_permission(t_redir *redir, int *exit_code)
{
	if (redir->output_file)
	{
		
		if (access(redir->output_file, F_OK) == 0 && access(redir->output_file, W_OK) != 0)
		{
			err_no_permission(redir->output_file);
			*(exit_code) = 1;
			return (1);
		}
	}
	return (0);
}

void	handle_redirections(t_shell *shell, t_redir *redir, int *exit_code)
{
	int fd;
	if (validate_inputfile_permission(redir, exit_code))
		return ;
	if (redir->input_file && !redir->here_doc)
	{
		fd = open(redir->input_file, O_RDONLY);
		if (fd == -1)
		{
			err("open input file");
			*(exit_code) = 1;
		}
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

		if (validate_outputfile_permission(redir, exit_code))
			return ;
		else if (fd == -1)
			err("open output file");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (redir->input_file || redir->output_file)
	{
		if (!shell->parsed_cmd || !*shell->parsed_cmd)
			shell->exit_code = 0;
	}
}
