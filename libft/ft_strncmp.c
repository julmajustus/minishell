/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:14:06 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 18:22:02 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*a1;
	unsigned char	*a2;
	size_t			nb;

	nb = 0;
	a1 = (unsigned char *) s1;
	a2 = (unsigned char *) s2;
	while ((a1[nb] != '\0' || a2[nb] != '\0') && nb < n)
	{
		if (a1[nb] != a2[nb])
		{
			return (a1[nb] - a2[nb]);
		}
		nb++;
	}
	return (0);
}
