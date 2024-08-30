/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:34:50 by jmakkone          #+#    #+#             */
/*   Updated: 2024/04/25 13:35:27 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	find;
	size_t	slen;

	ptr = (char *)s;
	find = (char)c;
	slen = ft_strlen(s);
	while (slen > 0)
	{
		if (ptr[slen] == find)
			return (ptr + slen);
		slen--;
	}
	if (ptr[slen] == find)
		return (ptr);
	return (NULL);
}
