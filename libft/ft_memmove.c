/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:04:53 by jmakkone          #+#    #+#             */
/*   Updated: 2024/04/25 13:32:42 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ndst;
	unsigned char const	*nsrc;

	ndst = dst;
	nsrc = src;
	if (!dst && !src)
		return (NULL);
	if (ndst < nsrc)
	{
		while (len--)
			*ndst++ = *nsrc++;
	}
	else
	{
		ndst = (ndst + len) - 1;
		nsrc = (nsrc + len) - 1;
		while (len--)
			*ndst-- = *nsrc--;
	}
	return (dst);
}
