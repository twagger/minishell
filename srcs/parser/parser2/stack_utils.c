/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:56:52 by twagner           #+#    #+#             */
/*   Updated: 2022/01/07 08:34:58 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser2.h"

int	ms_push_input(t_stack **stack, t_token *input)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->type = input->type;
	new->state = -1;
	new->data = input->value;
	new->next = *stack;
	*stack = new;
	return (OK);
}

int	ms_push_reduction(t_stack **stack, int reduction)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->type = reduction;
	new->state = -1;
	new->data = NULL;
	new->next = *stack;
	*stack = new;
	return (OK);
}

int	ms_push_state(t_stack **stack, int state)
{
	t_stack	*new;

	if (state == ERROR)
		return (ERROR);
	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->type = -1;
	new->state = state;
	new->data = NULL;
	new->next = *stack;
	*stack = new;
	return (OK);
}

// pop stack

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