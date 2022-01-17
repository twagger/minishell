/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:56:52 by twagner           #+#    #+#             */
/*   Updated: 2022/01/17 19:03:40 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** BASIC STACK MANIPULATION
*/

void	ms_add_popped(t_stack **popped, t_stack *stack)
{
	t_stack	*begin;

	if (!(*popped))
		*popped = stack;
	else
	{
		begin = *popped;
		while ((*popped)->next)
			*popped = (*popped)->next;
		(*popped)->next = stack;
		*popped = begin;
	}
	stack->next = NULL;
}

t_stack	*ms_pop_stack(t_stack **stack, int nb)
{
	int		i;
	t_stack	*next;
	t_stack	*popped;

	popped = NULL;
	if (stack)
	{
		i = -1;
		while (++i < nb)
		{
			next = (*stack)->next;
			free(*stack);
			*stack = next;
			next = (*stack)->next;
			ms_add_popped(&popped, *stack);
			*stack = next;
		}
	}
	return (popped);
}

void	ms_clear_stack(t_stack *stack)
{
	t_stack	*next;

	while (stack)
	{
		next = stack->next;
		free(stack->data);
		free(stack);
		stack = next;
	}
}

t_stack	*ms_init_stack(void)
{
	t_stack	*state_0;

	state_0 = (t_stack *)malloc(sizeof(*state_0));
	if (!state_0)
		return (NULL);
	state_0->data = NULL;
	state_0->state = 0;
	state_0->type = -1;
	state_0->next = NULL;
	return (state_0);
}

t_node	*ms_stack_to_node(t_stack *popped)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (node)
	{
		node->type = popped->type;
		node->reduc = -1;
		if (popped->type >= R_PIPE_SEQUENCE)
		{
			node->type = -1;
			node->reduc = popped->type;
		}
		node->data = popped->data;
		node->qt_rm = popped->qt_rm;
		popped->data = NULL;
		node->left = NULL;
		node->right = NULL;
		node->next = NULL;
		return (node);
	}
	return (NULL);
}
