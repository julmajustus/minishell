/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:09:12 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/02 19:37:12 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
	{
		ft_strlcpy(new_str, str, len + 2);
		free(str);
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
