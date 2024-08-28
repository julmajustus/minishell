/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:14:38 by jmakkone          #+#    #+#             */
/*   Updated: 2024/04/25 15:02:10 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_digits(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		while (n <= -10)
		{
			n /= 10;
			i++;
		}
	}
	else
	{
		while (n >= 10)
		{
			n /= 10;
			i++;
		}
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		dcount;
	long int	num;
	char		*str;

	num = n;
	dcount = count_digits(n);
	if (n < 0)
	{
		num *= -1;
		dcount++;
	}
	str = malloc((sizeof(char) * dcount) + 1);
	if (!str)
		return (NULL);
	*(str + dcount) = '\0';
	while (dcount--)
	{
		*(str + dcount) = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}
