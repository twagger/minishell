/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:55:16 by twagner           #+#    #+#             */
/*   Updated: 2022/01/06 23:10:48 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser2.h"

// Shift

// Reduce

// Accept

// Reject

// Parser

t_node	*ms_parser(t_token *input, t_trans **parsing_table)
{
	int		ret;
	t_node	*tree;
	t_trans *pt_entry;
	t_stack	*stack;
	
	ret = 0;
	tree = NULL;
	stack = init_stack();
	if (!stack)
		return (NULL);
	while (ret == RET_OK)
	{
		pt_entry = ms_get_entry(input, parsing_table, stack->state);
		if (pt_entry && pt_entry->action == ACT_SHIFT)
			ret = ms_shift(stack, input, pt_entry->next);
		else if (pt_entry && pt_entry->action == ACT_REDUCE)
			ret = ms_reduce(stack, pt_entry->next, pt_entry->nb_reduce, &tree);
		else if (pt_entry &&pt_entry->action == ACT_ACCEPT)
			ret = ms_accept();
		else
			ret = ms_reject();
	}
	if (ret == RET_CLEAR_TREE)
		ms_clear_tree(&tree);
	ms_clear_stack(stack);
	ms_clear_input(input);
	return (tree);
}