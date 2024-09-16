/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:19:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/15 14:45:18 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void push_to_stack(t_cmd_stack **stack, char *cmd)
{
	t_cmd_stack	*new_node;

	new_node = malloc(sizeof(t_cmd_stack));
	if (!new_node)
		return ;
	new_node->cmd = ft_strdup(cmd);
	new_node->next = *stack;
	*stack = new_node;
}

void	pop_from_stack(t_shell *shell, t_cmd_stack **stack, char **cmd)
{
	t_cmd_stack	*node;

	(void)shell;
	node = *stack;
	if (node == NULL)
		return;
	*cmd = node->cmd;
	*stack = node->next;
	free(node);
}

int	stack_len(t_cmd_stack **stack)
{
	t_cmd_stack	*node;
	int			i;

	node = *stack;
	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

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
		free(current_node);
		current_node = next_node;
	}
	*stack = NULL;
}
