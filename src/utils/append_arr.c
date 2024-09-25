/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:40:58 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/24 13:35:47 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_array(char *content, char ***new_arr, int *new_arr_size)
{
	*new_arr = ft_realloc(*new_arr, \
					sizeof(char *) * *new_arr_size, \
					sizeof(char *) * (*new_arr_size + 2));
	if (!*new_arr)
	{
		err("realloc failed!");
		return ;
	}
	(*new_arr)[*new_arr_size] = ft_strdup(content);
	*new_arr_size += 1;
}
