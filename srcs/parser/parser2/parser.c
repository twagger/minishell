/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:55:16 by twagner           #+#    #+#             */
/*   Updated: 2022/01/07 08:49:40 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser2.h"

static int	ms_shift(t_stack **stack, t_token *input, int next_state)
{
	if (ms_push_input(stack, input) == ERROR)
		return (ERROR);
	if (ms_push_state(stack, next_state) == ERROR)
		return (ERROR);
	return (OK);
}

int	ms_reduce(\
	t_stack **stack, t_trans **parsing_table, t_trans *pt_entry, t_node **tree)
{
	int		next_state;
	t_stack	*popped;

	popped = pop_stack(stack, pt_entry->nb_reduce);
	if (popped)
	{
		if (!ms_push_reduction(stack, pt_entry->next))
		{
			next_state = ms_get_next_state(stack, parsing_table);
			if (!ms_push_state(stack, next_state))
			{
				if (!ms_add_tree(tree, popped, pt_entry->next))
				{
					ms_clear_stack(popped);
					return (OK);
				}
			}
		}
		ms_clear_stack(popped);
	}
	return (ERROR);
}

int	ms_accept(void)
{
	return (1);
}

int	ms_reject(void)
{
	return (ERROR);
}

t_node	*ms_parser(t_token *input, t_trans **parsing_table)
{
	int		ret;
	t_node	*tree;
	t_trans *pt_entry;
	t_stack	*stack;
	
	ret = OK;
	tree = NULL;
	stack = init_stack();
	if (!stack)
		return (NULL);
	while (ret == OK)
	{
		pt_entry = ms_get_entry(input, parsing_table, stack->state);
		if (pt_entry && pt_entry->action == ACT_SHIFT)
			ret = ms_shift(&stack, input, pt_entry->next);
		else if (pt_entry && pt_entry->action == ACT_REDUCE)
			ret = ms_reduce(&stack, parsing_table, pt_entry, &tree);
		else if (pt_entry &&pt_entry->action == ACT_ACCEPT)
			ret = ms_accept();
		else
			ret = ms_reject();
	}
	if (ret == ERROR)
		ms_clear_tree(&tree);
	ms_clear_stack(stack);
	ms_clear_input(input);
	return (tree);
}