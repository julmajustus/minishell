/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:02:53 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/06 16:44:02 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int is_redirection_operator(const char *token)
{
    return (!strcmp(token, "<") || !strcmp(token, "<<") || 
            !strcmp(token, ">") || !strcmp(token, ">>"));
}

static void	reorganize_parsed_cmd(t_shell *shell)
{	
	char **new_cmd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_cmd = malloc(sizeof(char *) * (arr_len(shell->parsed_cmd)));
	init_arr(new_cmd, arr_len(shell->parsed_cmd));
	while (shell->parsed_cmd[i])
	{
		if (is_redirection_operator(shell->parsed_cmd[i]))
			i += 2;
		else
		 	new_cmd[j++] = ft_strdup(shell->parsed_cmd[i++]);
	}
	new_cmd[j] = NULL;
	free_arr(shell->parsed_cmd);
	shell->parsed_cmd = new_cmd;
}

void	parse_redirections(t_shell *shell)
{
	int	i;
	int redir_count;

	i = 0;
	redir_count = 0;
	while (shell->parsed_cmd[i]) 
	{
		if (ft_strcmp(shell->parsed_cmd[i], "<") == 0 && shell->parsed_cmd[i + 1])
		{
			shell->redir->input_file = ft_strdup(shell->parsed_cmd[i + 1]);
			redir_count++;
		}
		else if (ft_strcmp(shell->parsed_cmd[i], ">") == 0 && shell->parsed_cmd[i + 1])
		{
			shell->redir->output_file = ft_strdup(shell->parsed_cmd[i + 1]);
			shell->redir->append_mode = 0;
			redir_count++;
		}
		else if (ft_strcmp(shell->parsed_cmd[i], ">>") == 0 && shell->parsed_cmd[i + 1])
		{
			shell->redir->output_file = ft_strdup(shell->parsed_cmd[i + 1]);
			shell->redir->append_mode = 1;
			redir_count++;
		}
		else if (ft_strcmp(shell->parsed_cmd[i], "<<") == 0 && shell->parsed_cmd[i + 1])
		{
			shell->redir->here_doc = 1;
			shell->redir->input_file = ft_strdup(shell->parsed_cmd[i + 1]);
			redir_count++;
		}
		i++;
	}
	if (redir_count)
		reorganize_parsed_cmd(shell);
}

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
		here_doc(redir->input_file, &fd);
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
