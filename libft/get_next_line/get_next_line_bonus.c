/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:36:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/06 23:48:23 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*append_to_static_buf(char **static_buf, char *read_buf)
{
	char	*tmp;

	tmp = *static_buf;
	*static_buf = ft_strjoin(tmp, read_buf);
	free(tmp);
	return (*static_buf);
}

static char	*read_fd(int fd, char *read_buf, char **static_buf)
{
	ssize_t	read_count;

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
		if (!append_to_static_buf(static_buf, read_buf))
			return (NULL);
		if (ft_strchr(read_buf, '\n'))
			break ;
	}
	return (*static_buf);
}

static char	*get_line(char *static_buf)
{
	size_t	i;
	char	*new_line;

	if (!static_buf || *static_buf == '\0')
		return (NULL);
	i = 0;
	while (static_buf[i] && static_buf[i] != '\n')
		i++;
	if (static_buf[i] == '\n')
		i++;
	new_line = ft_substr(static_buf, 0, i);
	if (!new_line)
		return (NULL);
	return (new_line);
}

static char	*update_static_buf(char *static_buf, char *line)
{
	size_t	len;
	char	*new_static_buf;

	len = ft_strlen(line);
	if (!static_buf[len])
	{
		free(static_buf);
		return (NULL);
	}
	new_static_buf = ft_strdup(static_buf + len);
	free(static_buf);
	if (!new_static_buf)
		return (NULL);
	return (new_static_buf);
}

char	*get_next_line(int fd)
{
	static char	*static_buf[MAX_FD];
	char		read_buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	static_buf[fd] = read_fd(fd, read_buf, &static_buf[fd]);
	if (!static_buf[fd])
		return (NULL);
	line = get_line(static_buf[fd]);
	if (!line)
	{
		free(static_buf[fd]);
		static_buf[fd] = NULL;
		return (NULL);
	}
	static_buf[fd] = update_static_buf(static_buf[fd], line);
	return (line);
}
