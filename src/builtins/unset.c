/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:45:45 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 14:25:25 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(char **envp, char *str)
{
	// maybe need to handle error case if envp is NULL
	 //Added check for the equalsing just to handle only cases where only VAR name is given
	if (!str || !*str || ft_strchr(str, '='))
		return (envp);
	return (delete_env_line(envp, str));
}
