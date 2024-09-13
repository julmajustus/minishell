/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:42:27 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/12 23:29:07 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_stack(t_cmd_stack **stack)
{	
    t_cmd_stack	*current_node;
    t_cmd_stack	*next_node;

	if (stack == NULL || *stack == NULL)
		return ;
    current_node = *stack;
    
    while (current_node)
	{
        next_node = current_node->next;
        if (current_node->cmd)
            free(current_node->cmd);
        if (current_node->token)
            free(current_node->token);
        free(current_node);
        current_node = next_node;
    }
    *stack = NULL;
}
