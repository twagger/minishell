/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:27:24 by twagner           #+#    #+#             */
/*   Updated: 2022/01/04 15:27:36 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_stack	*ms_pop_stack(t_stack **stack, int nb)
{
	int		i;
	t_stack	*next;
	t_stack	*popped;
	t_stack	*begin;

	popped = NULL;
	begin = NULL;
	if (stack)
	{
		i = 0;
		while (i < nb)
		{
			next = (*stack)->next;
			ms_free_stack_item(*stack);
			*stack = next;
			next = (*stack)->next;
			if (!popped)
			{
				popped = *stack;
				begin = popped;
			}
			else
			{
				popped->next = *stack;
				popped = popped->next;
			}
			*stack = next;
			++i;
		}
		popped->next = NULL;
	}
	return (begin);
}

int	ms_add_front(t_stack **stack, t_stack *item)
{
	if (!item)
		return (ERROR);
	item->next = *stack;
	*stack = item;
	return (EXIT_SUCCESS);
}

void	ms_free_stack_item(t_stack *stack)
{
	if (stack)
	{
		free(stack->data);
		free(stack);
	}
}

int	ms_free_stack(t_stack *stack, int return_code)
{
	t_stack	*next;

	while (stack)
	{
		next = stack->next;
		ms_free_stack_item(stack);
		stack = next;
	}
	return (return_code);
}
