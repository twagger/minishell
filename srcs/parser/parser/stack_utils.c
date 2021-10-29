/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:27:24 by twagner           #+#    #+#             */
/*   Updated: 2021/10/29 14:20:26 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lr_parser.h"

t_stack	*ms_new_stack_item(void *content, int type, int state)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = type;
	new->state = state;
	new->data = content;
	new->next = NULL;
	return (new);
}

t_stack	*ms_pop_stack(t_stack **stack)
{
	t_stack	*res;

	res = *stack;
	*stack = (*stack)->next;
	return (res);
}

void	ms_add_front(t_stack **stack, t_stack *item)
{
	if (item)
	{
		item->next = *stack;
		*stack = item;
	}
}

void	ms_free_stack_item(t_stack *stack)
{
	if (stack)
	{
		free(stack->data);
		free(stack);
	}
}

void	ms_free_stack(t_stack **stack)
{
	if (stack)
	{
		while (*stack)
		{
			ms_free_stack_item(*stack);
			++stack;
		}
	}
}
