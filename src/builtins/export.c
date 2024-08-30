/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:34:23 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/29 23:35:28 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export(char **envp, char *str)
{
	if (!envp || !*envp || !str || !*str)
		return (NULL);
	return (replace_or_create_env_line(envp, str));
}
