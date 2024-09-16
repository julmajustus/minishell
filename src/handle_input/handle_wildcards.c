/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:45:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/17 00:13:59 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	check_if_wildcards(t_shell *shell)
{
	int	i;
	
	i  = -1;
	while(shell->parsed_cmd[++i])
	{
		if(ft_strchr(shell->parsed_cmd[i], '*'))
			return (1);
	}
	return (0);
}

static int	match_pattern(const char *pattern, const char *str)
{
	const char *p;
	const char *s;

	p = pattern;
	s = str;
	while (*p && *s)
	{
		if (*p == '*')
		{
			while (*p == '*')
				p++;
			if (*p == '\0')
				return (1);
			while (*s && !match_pattern(p, s++))
				return (*s != '\0');
		}
		else if (*p != *s)
			return (0);
		p++;
		s++;
	}
	if (*p == '*' && *(p + 1) == '\0')
		return (1);
	return (*p == '\0' && *s == '\0');
}

static void append_cmd_array(char *cmd, char ***new_cmd, int *new_cmd_size)
{
	*new_cmd = ft_realloc(*new_cmd, \
					  sizeof(char *) * *new_cmd_size, \
					  sizeof(char *) * (*new_cmd_size + 2));
	if (!*new_cmd)
	{
		err("realloc failed!");
		return ;
	}
	(*new_cmd)[*new_cmd_size] = ft_strdup(cmd);
	*new_cmd_size += 1;
}

static int read_directory(t_shell *shell, char ***new_cmd, int *i, int *new_cmd_size)
{
	struct dirent	*entry;
	DIR				*dir;
	int				match_count;

	match_count = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		err("opendir");
		return (-1);
	}
	while (ft_strchr(shell->parsed_cmd[*i], '*'))
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (match_pattern(shell->parsed_cmd[*i], entry->d_name))
		{
			append_cmd_array(entry->d_name, new_cmd, new_cmd_size);
			match_count++;
		}
	}
	closedir(dir);
	return (match_count);
}

void	handle_wildcards(t_shell *shell)
{
	char	**new_cmd;
	int		new_cmd_size;
	int		i;

	new_cmd = NULL;
	new_cmd_size = 0;
	i = -1;
	while (shell->parsed_cmd[++i])
	{
		if (read_directory(shell, &new_cmd, &i, &new_cmd_size))
			;
		else
			append_cmd_array(shell->parsed_cmd[i], &new_cmd, &new_cmd_size);
	}
	new_cmd = ft_realloc(new_cmd, \
					  sizeof(char *) * new_cmd_size, \
					  sizeof(char *) * (new_cmd_size + 1));
	if (new_cmd)
		new_cmd[new_cmd_size] = NULL;
	free_arr(shell->parsed_cmd);
	shell->parsed_cmd = new_cmd;
}
