/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:29:59 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 01:34:30 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_arg(char **args, char *arg, size_t *argc, size_t *arg_size)
{
	char	**new_args;
	size_t	i;

	i = 0;
	if (*argc >= *arg_size)
	{
		*arg_size *= 2;
		new_args = malloc(*arg_size * sizeof(char *));
		if (!new_args)
			return (NULL);
		while (i < *argc)
		{
			new_args[i] = args[i];
			i++;
		}
		free(args);
		args = new_args;
	}
	args[*argc] = arg;
	(*argc)++;
	return (args);
}
