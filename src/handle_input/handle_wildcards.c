/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:45:03 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/16 13:47:42 by jmakkone         ###   ########.fr       */
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

static int	locate_wildcard(char * cmd)
{
	if (ft_strchr(cmd, '*'))
		return (1);
	return (0);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	*old_ptr;
	size_t	old_size;
	size_t	copy_size;

	if (new_size == 0)
	{
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	old_ptr = (size_t *)ptr - 1;
	old_size = *old_ptr;
	if (new_size < old_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return new_ptr;
}

static int	match_pattern(const char *pattern, const char *str)
{
	const char *p = pattern;
	const char *s = str;

	while (*p && *s)
	{
		if (*p == '*')
		{
			while (*p == '*') p++;
			if (*p == '\0') return 1;
			while (*s)
			{
				if (match_pattern(p, s)) return 1;
				s++;
			}
			return 0;
		}
		else if (*p != *s)
			return 0;
		p++;
		s++;
	}
	return *p == '\0' && *s == '\0';
}

void	handle_wildcards(t_shell *shell)
{
	char **new_cmd = NULL;
	struct dirent *entry;
	int new_cmd_size = 0;
	int i = 0;

	while (shell->parsed_cmd[i])
	{
		if (locate_wildcard(shell->parsed_cmd[i]))
		{
			//printf("Found a wildcard[%d]: %s\n", i,  shell->parsed_cmd[i]);
			DIR *dir = opendir(".");
			if (dir == NULL) {
				err("opendir");
				continue;
			}
			while ((entry = readdir(dir)) != NULL)
			{
				if (match_pattern(shell->parsed_cmd[i], entry->d_name))
				{
					new_cmd = ft_realloc(new_cmd, sizeof(char *) * (new_cmd_size + 2));
					new_cmd[new_cmd_size] = ft_strdup(entry->d_name);
					new_cmd_size++;
				}
			}
			closedir(dir);
		}
		else
		{
			//printf("Did not find any wildcards.\n");
			new_cmd = ft_realloc(new_cmd, sizeof(char *) * (new_cmd_size + 2));
			new_cmd[new_cmd_size] = ft_strdup(shell->parsed_cmd[i]);
			new_cmd_size++;
		}
		i++;
	}

	new_cmd[new_cmd_size] = NULL;
	free_arr(shell->parsed_cmd);
	shell->parsed_cmd = new_cmd;
}
