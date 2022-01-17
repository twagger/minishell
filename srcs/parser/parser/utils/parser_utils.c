/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:55:15 by twagner           #+#    #+#             */
/*   Updated: 2022/01/17 19:04:54 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** PUSH INTO THE STACK
** Push input for the shift operation
** Push reduction for the reduce operation
** Push state for shift and reduce
*/

int	ms_push_input(t_stack **stack, t_token *input)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->type = input->type;
	new->qt_rm = input->qt_rm;
	new->state = -1;
	new->data = input->value;
	input->value = NULL;
	new->next = *stack;
	*stack = new;
	return (RET_OK);
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
	return (RET_OK);
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
	return (RET_OK);
}
/*
** GET NEXT STATE
** Used by the reduce operation to find the next state after a reduction
*/

int	ms_get_next_state(t_stack *stack, t_trans **parsing_table)
{
	int	i;
	int	state;
	int	next_state;

	state = stack->next->state;
	i = -1;
	while (parsing_table[++i])
	{
		if (parsing_table[i]->state == state)
		{
			if (parsing_table[i]->event == stack->type)
				return (parsing_table[i]->next);
			else if (parsing_table[i]->event == DEFAULT)
				next_state = parsing_table[i]->next;
		}
	}
	return (next_state);
}

/*
** GET ENTRY
** Used by the parser to find the right entry in the parsing table according
** to the input and the current state.
*/

t_trans	*ms_get_entry(t_token *input, t_trans **parsing_table, t_stack *stack)
{
	int		i;
	int		input_type;
	t_trans	*table_entry;

	if (!stack)
		return (NULL);
	table_entry = NULL;
	input_type = -1;
	if (input)
		input_type = input->type;
	i = -1;
	while (parsing_table[++i])
	{
		if (parsing_table[i]->state == stack->state)
		{
			if (parsing_table[i]->event == input_type)
				return (parsing_table[i]);
			else if (parsing_table[i]->event == DEFAULT)
				table_entry = parsing_table[i];
		}
	}
	return (table_entry);
}
