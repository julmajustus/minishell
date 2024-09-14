/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:19:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/14 16:59:57 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void push_to_bottom_of_stack(t_cmd_stack **stack, char *cmd, char *token)
{
    t_cmd_stack *new_node;
    t_cmd_stack *temp;

    new_node = malloc(sizeof(t_cmd_stack));
    if (!new_node)
        return;
    new_node->cmd = ft_strdup(cmd);
	if (token)
		new_node->token = ft_strdup(token);
	else
		new_node->token = NULL;
	new_node->next = NULL;
	if (*stack == NULL)
	{
		*stack = new_node;
		return;
	}
	temp = *stack;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new_node;
}

void push_to_stack(t_cmd_stack **stack, char *cmd, char *token, int push_to_bottom)
{
	t_cmd_stack	*new_node;
	if (push_to_bottom == 1)
		push_to_bottom_of_stack(stack, cmd, token);
	else
	{
		new_node = malloc(sizeof(t_cmd_stack));
		if (!new_node)
			return ;
		new_node->cmd = ft_strdup(cmd);
		if (token)
			new_node->token = ft_strdup(token);
		else
			new_node->token = NULL;
		new_node->next = *stack;
		*stack = new_node;
	}
}

void	pop_from_stack(t_shell *shell, t_cmd_stack **stack, char **cmd, char **token)
{
	t_cmd_stack	*node;

	(void)shell;
	node = *stack;
	if (node == NULL)
		return;
	*cmd = node->cmd;
	*token = node->token;
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
        if (current_node->token)
            free(current_node->token);
        free(current_node);
        current_node = next_node;
    }
    *stack = NULL;
}
