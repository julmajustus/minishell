/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:48:02 by jmakkone          #+#    #+#             */
/*   Updated: 2024/04/29 08:31:32 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nmemb * size;
	if (total > 0 && nmemb > 0 && (total / size != nmemb))
		return (NULL);
	ptr = malloc(total);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, total);
	return (ptr);
}
