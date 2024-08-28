/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:46:22 by jmakkone          #+#    #+#             */
/*   Updated: 2024/04/25 13:35:01 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			len;
	char			*ptr;
	unsigned char	uc;

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
