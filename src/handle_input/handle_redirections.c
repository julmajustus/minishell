/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:02:53 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/26 03:04:38 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_inputfile_permission(t_shell *shell)
{
	int	i;

	if (shell->redir->input_file && !shell->redir->here_doc)
	{
		i = -1;
		while (shell->redir->input_file[++i])
		{
			if (access(shell->redir->input_file[i], F_OK) != 0)
			{
				if (!shell->exit_code)
					err_nofile(shell->redir->input_file[i]);
				shell->exit_code = 1;
				return (1);
			}
			if (access(shell->redir->input_file[i], R_OK) != 0)
			{
				if (!shell->exit_code)
					err_no_permission(shell->redir->input_file[i]);
				shell->exit_code = 1;
				return (1);
			}
		}
	}
	return (0);
}

static int	validate_outputfile_permission(char *output_file, int *exit_code)
{
	if (output_file)
	{
		if (access(output_file, F_OK) == 0 && access(output_file, W_OK) != 0)
		{
			if (!*(exit_code))
				err_no_permission(output_file);
			*(exit_code) = 1;
			return (1);
		}
	}
	return (0);
}

static void	handle_input_files(t_shell *shell)
{
	int i;
	int fd;

	if (shell->redir->syntax_err == 0)
		exit_syntax_error(shell, "<<");
	if (shell->redir->input_file && !shell->redir->here_doc)
	{
		i = -1;
		while (shell->redir->input_file[++i])
		{
			fd = open(shell->redir->input_file[i], O_RDONLY);
			if (fd == -1)
			{
				err("open input file");
				shell->exit_code = 1;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
}

static void	handle_output_files(t_shell *shell)
{
	int i;
	int fd;
	if (shell->redir->syntax_err == 1)
		exit_syntax_error(shell, ">>");
	if (shell->redir->output_file)
	{
		i = -1;
		while (shell->redir->output_file[++i])
		{
			if (shell->redir->append_mode)
				fd = open(shell->redir->output_file[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(shell->redir->output_file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);

			if (validate_outputfile_permission(shell->redir->output_file[i], &shell->exit_code))
				return ;
			if (fd == -1)
				err("open output file");
			dup2(fd, STDOUT_FILENO);
			close(fd);

		}
	}
}

void	handle_redirections(t_shell *shell)
{
	if (shell->redir->output_file_first)
	{
		handle_output_files(shell);
		if (validate_inputfile_permission(shell))
			return ;
		handle_input_files(shell);
		handle_here_doc(shell);
	}
	else
	{
		if (validate_inputfile_permission(shell))
			return ;
		handle_input_files(shell);
		handle_here_doc(shell);
		handle_output_files(shell);
	}
	if (shell->redir->input_file || shell->redir->output_file || \
		shell->redir->here_doc_eof)
	{
		if (!shell->parsed_cmd || !*shell->parsed_cmd)
		{	
			free_shell_allocations(shell);
			exit(EXIT_SUCCESS);
		}
	}
}
