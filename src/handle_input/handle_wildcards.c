/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:45:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/27 01:35:33 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	match_wildcard(const char *pattern, const char *str)
{
	const char *p;
	const char *s;

	p = pattern;
	s = str;
	while (*p == '*')
		p++;
	if (*p == '\0')
		return (1);
	while (*s)
	{
		if (match_pattern(p, s))
			return (1);
		s++;
	}
	return (0);
}

int	match_pattern(const char *pattern, const char *str)
{
	const char *p;
	const char *s;

	p = pattern;
	s = str;
	while (*p && *s)
	{
		while (*p == '<' || *p == '>')
			p++;
		if (*p == '*')
			return match_wildcard(p, s);
		else if (*p != *s)
			return (0);
		p++;
		s++;
	}
	if (*p == '*' && *(p + 1) == '\0')
		return (1);
	return (*p == '\0' && *s == '\0');
}

static int append_matches(t_shell *shell, char ***new_cmd, int *i, int *new_cmd_size)
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
	while (ft_strchr(shell->parsed_cmd[*i], '*') && \
			(!ft_strchr(shell->parsed_cmd[*i], '\'') || \
			!ft_strchr(shell->parsed_cmd[*i], '\"')))
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (match_pattern(shell->parsed_cmd[*i], entry->d_name))
		{
			append_array(entry->d_name, new_cmd, new_cmd_size);
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
		if (append_matches(shell, &new_cmd, &i, &new_cmd_size))
			;
		else
			append_array(shell->parsed_cmd[i], &new_cmd, &new_cmd_size);
	}
	free_arr_and_null(&shell->parsed_cmd);
	shell->parsed_cmd = new_cmd;
}
