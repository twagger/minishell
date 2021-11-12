/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:04:45 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 15:14:02 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** BUFFER THE TERM
** Put the popped term in the stack until it is reduced and can join the tree
*/

static int	ms_stack_to_buffer(\
	t_stack	*item, int reduction, t_ast_builder **builder)
{
	t_node	*new;

	if (item->type == T_WORD && reduction == R_HERE_END)
		item->type = A_LIMITER;
	if (item->type == T_WORD && reduction == R_FILENAME)
		item->type = A_FILE;
	new = ms_new_node(ft_strdup(item->data), item->type, reduction);
	if (!new || (new && !new->data))
		return (ERROR);
	if (ms_buffer_add_back(builder, new) == ERROR)
	{
		ms_free_tree(new);
		return (ERROR);
	}
	ms_free_stack_item(item);
	return (EXIT_SUCCESS);
}

/*
** FIND THE TERM IN THE BUFFER OR AST ROOT
** Search and return the last node that has been reduced to the searched rule
*/

t_node	*ms_get_popped(t_ast_builder **builder, int reduc, int action)
{
	int	i;

	i = -1;
	while ((*builder)->buffer[++i])
	{
		if ((*builder)->buffer[i]->reduc == reduc)
		{
			if (action == KEEP)
				return ((*builder)->buffer[i]);
			else if (action == POP)
				return (ms_buffer_remove(builder, i));
		}
	}
	if ((*builder)->ast && (*builder)->ast->reduc == reduc)
		return ((*builder)->ast);
	return (NULL);
}

/*
** BUILD THE TREE
** This function connects the right nodes under the current reduction node to 
** create a tree. The tree it then pushed to the ast or stays in the buffer.
*/

static int	ms_apply_reduction(\
	t_ast_builder **builder, t_stack **popped, int reduction, int nb)
{
	t_node	*node;

	if (nb == 1)
	{
		node = ms_get_popped(builder, popped[0]->type, KEEP);
		if (!node)
			return (ERROR);
		node->reduc = reduction;
		return (EXIT_SUCCESS);
	}
	node = ms_new_node(NULL, -1, reduction);
	if (!node)
		return (ERROR);
	if (ms_build_subtree(builder, popped, reduction, &node) == ERROR)
		return (ERROR);
	if (!(*builder)->ast \
		|| ((*builder)->ast && (*builder)->ast == node->left) \
		|| ((*builder)->ast && (*builder)->ast == node->right))
		(*builder)->ast = node;
	else
	{
		if (ms_buffer_add_back(builder, node) == ERROR)
			return (ERROR);
	}
	return (EXIT_SUCCESS);
}

/*
** BUILDER
** Get a list of popped terms (terminal or not) and a reduction code and 
** build a binary tree from bottom - left to top.
*/

int	ms_ast_builder(t_ast_builder **builder, t_stack **popped, int reduc)
{
	int	nb;

	nb = 0;
	while (popped[nb])
		++nb;
	if (nb == 1 && popped[0]->type < 100)
	{
		if (ms_stack_to_buffer(popped[0], reduc, builder) == ERROR)
			return (ERROR);
	}
	else
	{
		if (ms_apply_reduction(builder, popped, reduc, nb) == ERROR)
			return (ERROR);
	}
	return (EXIT_SUCCESS);
}
