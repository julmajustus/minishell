/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:11:04 by jmakkone          #+#    #+#             */
/*   Updated: 2024/04/25 13:31:06 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*nstr;

	i = 0;
	nstr = (unsigned char *)b;
	while (i < len)
	{
		nstr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
