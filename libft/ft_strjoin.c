/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 05:19:46 by jmakkone          #+#    #+#             */
/*   Updated: 2024/04/25 15:00:39 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
