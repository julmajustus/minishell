/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:36:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/05/17 08:55:26 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (ptr);
}

static char	*read_fd(int fd, char *read_buf, char **static_buf)
{
	ssize_t	read_count;
	char	*tmp;

	read_count = 1;
	while (read_count)
	{
		read_count = read(fd, read_buf, BUFFER_SIZE);
		if (read_count == -1)
			return (ft_free(*static_buf));
		else if (read_count == 0)
			break ;
		read_buf[read_count] = '\0';
		if (!*static_buf)
		{
			*static_buf = ft_strdup("");
			if (!*static_buf)
				return (NULL);
		}
		tmp = *static_buf;
		*static_buf = ft_strjoin(tmp, read_buf);
		tmp = ft_free(tmp);
		if (ft_strchr(read_buf, '\n'))
			break ;
	}
	return (*static_buf);
}

static char	*get_line(char *static_buf)
{
	size_t	i;
	char	*new_line;

	i = 0;
	if (!static_buf)
		return (NULL);
	if (static_buf[i] == '\n' || static_buf[i] == '\0')
	{
		new_line = ft_substr(static_buf, 0, 1);
		if (!new_line)
			return (NULL);
	}
	else
	{
		while (static_buf[i] != '\n' && static_buf[i] != '\0')
			i++;
		new_line = ft_substr(static_buf, 0, i + 1);
		if (!new_line)
			return (NULL);
	}
	if (!*new_line)
		return (ft_free(new_line));
	return (new_line);
}

static char	*update_static_buf(char *static_buf, char *line)
{
	char	*new_static_buf;

	new_static_buf = static_buf;
	static_buf = ft_strdup(new_static_buf + ft_strlen(line));
	new_static_buf = ft_free(new_static_buf);
	return (static_buf);
}

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		read_buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	static_buf = read_fd(fd, read_buf, &static_buf);
	line = get_line(static_buf);
	if (!line)
	{
		static_buf = ft_free(static_buf);
		return (NULL);
	}
	static_buf = update_static_buf(static_buf, line);
	return (line);
}
