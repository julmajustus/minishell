/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:19:25 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/13 03:19:58 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void push_to_bottom_of_stack(t_cmd_stack **stack, char *cmd, char *token)
{
    t_cmd_stack *new_node;
    t_cmd_stack *temp;

//	printf("Check cmd: %s and its token: %s\n", cmd, token);
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
	if (push_to_bottom > 1)
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

void	pop_from_stack(t_cmd_stack **stack, char **cmd, char **token)
{
	t_cmd_stack	*node;

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
