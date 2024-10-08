/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 00:02:16 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 13:32:58 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_arr(char **arr, int arr_len)
{
	int	i;

	i = -1;
	while (++i < arr_len)
		arr[i] = NULL;
}
