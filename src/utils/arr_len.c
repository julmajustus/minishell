/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:55:42 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 13:35:13 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_len(char **arr)
{
	int	len;

	if (!arr || !*(arr))
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}
