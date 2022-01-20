/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:55:16 by twagner           #+#    #+#             */
/*   Updated: 2022/01/20 20:12:51 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** SHIFT
** Shift the current input into the stack and add the next state on top.
*/

static int	ms_shift(t_stack **stack, t_token **input, int next_state)
{
	if (ms_push_input(stack, *input) == ERROR)
		return (ERROR);
	if (ms_push_state(stack, next_state) == ERROR)
		return (ERROR);
	*input = (*input)->next;
	return (RET_OK);
}

/*
** REDUCE
** Pop the stack and replace the popped elements with a reduction. Add the
** next step on top and complete the output (tree) with the popped elements.
*/

int	ms_reduce(\
	t_stack **stack, t_trans **parsing_table, t_trans *pt_entry, t_node **tree)
{
	int		next_state;
	t_stack	*popped;

	popped = ms_pop_stack(stack, pt_entry->nb_reduce);
	if (popped)
	{
		if (!ms_push_reduction(stack, pt_entry->next))
		{
			next_state = ms_get_next_state(*stack, parsing_table);
			if (!ms_push_state(stack, next_state))
			{
				if (!ms_add_tree(tree, &popped, pt_entry->next))
				{
					ms_clear_stack(popped);
					return (RET_OK);
				}
			}
		}
		ms_clear_stack(popped);
	}
	return (ERROR);
}

/*
** ACCEPT
** Accept the command line. This will trigger the return of the output to
** the main function.
*/

int	ms_accept(void)
{
	return (1);
}

/*
** REJECT
** Reject the command line. This will trigger the cleaningof the allocated
** resources and a NULL return. 
*/

int	ms_reject(void)
{
	return (ERROR);
}

/*
** PARSER
** The parser will browse the input and shift or reduce the tokens
** until the command is accepted or rejected. The parser also produces
** and returns an output (synthax tree).
*/

t_node	*ms_parser(t_token *input, t_trans **parsing_table)
{
	int		ret;
	t_node	*tree;
	t_trans	*pt_entry;
	t_stack	*stack;
	t_token	*input_begin;

	ret = RET_OK;
	tree = NULL;
	input_begin = input;
	stack = ms_init_stack();
	while (ret == RET_OK)
	{
		pt_entry = ms_get_entry(input, parsing_table, stack);
		if (pt_entry && pt_entry->action == ACT_SHIFT)
			ret = ms_shift(&stack, &input, pt_entry->next);
		else if (pt_entry && pt_entry->action == ACT_REDUCE)
			ret = ms_reduce(&stack, parsing_table, pt_entry, &tree);
		else if (pt_entry && pt_entry->action == ACT_ACCEPT)
			ret = ms_accept();
		else
			ret = ms_reject();
	}
	ms_parser_cleaning(&tree, stack, input_begin, ret);
	return (ms_fix_param_types(tree));
}
