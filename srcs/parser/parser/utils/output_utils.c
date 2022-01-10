/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:59:05 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 14:24:21 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** REMOVE NODE FROM LIST
** Remove a node from the node list that will be attached under a reduction
** node
*/

void	ms_remove_node_from_list(t_node **tree, t_node *node)
{
	t_node	*previous;
	t_node	*tmp;

	if (*tree == node)
	{
		*tree = node->next;
		return ;
	}
	else
	{
		previous = NULL;
		tmp = *tree;
		while (tmp)
		{
			if (tmp == node)
			{
				previous->next = tmp->next;
				return ;
			}
			previous = tmp;
			tmp = tmp->next;
		}
	}
}

/*
** SEARCH REDUCTION
** Search for a reduction node in the node list to attach it
** under the current reduction node.
*/

t_node	*ms_search_reduction(t_node **tree, int reduction)
{
	t_node	*begin;
	t_node	*result;

	result = NULL;
	begin = *tree;
	*tree = (*tree)->next;
	while (*tree)
	{
		if ((*tree)->reduc == reduction)
		{
			result = *tree;
			ms_remove_node_from_list(&begin, *tree);
			break ;
		}
		*tree = (*tree)->next;
	}
	*tree = begin;
	return (result);
}

/*
** ADD REDUCTION FRONT
** Creates a node for the current reduction and adds it in front
** of the node list;
*/

t_node	*ms_add_reduction_front(t_node **tree, int reduction)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(*node));
	if (node)
	{
		node->type = -1;
		node->reduc = reduction;
		node->data = NULL;
		node->left = NULL;
		node->right = NULL;
		node->next = *tree;
		*tree = node;
		return (node);
	}
	return (NULL);
}

/*
** BUILD TREE
** Attach the right nodes under the reduction node.
*/

int	ms_build_tree(t_node **tree, t_node *reduc_node, t_stack **popped)
{
	int		i;
	t_node	*child;
	t_stack	*begin;

	i = -1;
	begin = *popped;
	while (*popped)
	{
		if ((*popped)->type >= 100)
			child = ms_search_reduction(tree, (*popped)->type);
		else
			child = ms_stack_to_node(*popped);
		if (!child)
			return (ERROR);
		if (++i == 0)
			reduc_node->right = child;
		else
			reduc_node->left = child;
		if (i == 1 && (*popped)->next)
			reduc_node = reduc_node->left;
		(*popped) = (*popped)->next;
	}
	*popped = begin;
	return (RET_OK);
}

/*
** ADD TREE
** Add the popped elements from the stack to the output tree, under
** the reduction node.
*/

int	ms_add_tree(t_node **tree, t_stack **popped, int reduction)
{
	t_node	*reduc_node;

	reduc_node = ms_add_reduction_front(tree, reduction);
	if (reduc_node)
	{
		if (!ms_build_tree(tree, reduc_node, popped))
			return (RET_OK);
	}
	return (ERROR);
}
