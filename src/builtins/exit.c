/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:47:07 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/04 14:51:55 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **envp, char **cmd)
{
	free_arr(envp);
	free_arr(cmd);
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}
