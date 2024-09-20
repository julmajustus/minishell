/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:49:34 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/17 13:49:49 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_wildcards(t_shell *shell)
{
	int	i;
	
	i  = -1;
	while(shell->parsed_cmd[++i])
	{
		if(ft_strchr(shell->parsed_cmd[i], '*'))
			return (1);
	}
	return (0);
}
