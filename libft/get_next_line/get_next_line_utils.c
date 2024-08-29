/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:45:32 by jmakkone          #+#    #+#             */
/*   Updated: 2024/05/17 01:40:23 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			len;
	char			*ptr;
	unsigned char	uc;

	if (!s)
		return (NULL);
	uc = (unsigned char)c;
	ptr = (char *)s;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*ptr == uc)
			return ((char *)ptr);
		ptr++;
	}
	if (uc == '\0')
		return ((char *)ptr);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*substr;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (start < slen && i < len)
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*ptr;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	ptr = str;
	while (*s)
		*str++ = *s++;
	*str = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	char	*ptr;
	size_t	jlen;

	jlen = (ft_strlen(s1) + ft_strlen(s2));
	jstr = (char *)malloc(jlen + 1);
	if (!jstr)
		return (NULL);
	ptr = jstr;
	while (*s1)
		*jstr++ = *s1++;
	while (*s2)
		*jstr++ = *s2++;
	*jstr = '\0';
	return (ptr);
}
