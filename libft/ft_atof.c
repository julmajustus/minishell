/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:47:11 by jmakkone          #+#    #+#             */
/*   Updated: 2024/07/19 01:38:07 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	int			msing;
	double		sum;
	double		d;

	msing = 1;
	sum = 0.0;
	d = 0.1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			msing = msing * -1;
		str++;
	}
	while (*str && ft_isdigit(*str) == 1 && *str != '.')
		sum = (sum * 10.0) + *str++ - 48;
	if (*str == '.')
		str++;
	while (*str && ft_isdigit(*str) == 1)
	{
		sum = sum + ((*str++ - 48) * d);
		d = d * 0.1;
	}
	return (sum * msing);
}
