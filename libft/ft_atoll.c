/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:25:15 by jmakkone          #+#    #+#             */
/*   Updated: 2024/06/22 18:11:21 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	int			msing;
	long long	sum;
	long long	check;

	msing = 1;
	sum = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			msing = msing * -1;
		str++;
	}
	while (*str && ft_isdigit(*str) == 1)
	{
		check = sum * 10 + *str - 48;
		if (check / 10 != sum && msing == 1)
			return (-1);
		if (check / 10 != sum && msing == -1)
			return (0);
		sum = check;
		str++;
	}
	return ((long long)sum * (long long)msing);
}
