/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_reducer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:31:00 by twagner           #+#    #+#             */
/*   Updated: 2021/11/11 15:52:36 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** AST REDUCER
** The ast reducer simplify the tree by removing all intermediate nodes and
** keeping operators and operands
*/

static t_node	*ms_promote_child(t_node *node)
{
	int		left_reduc;
	int		right_reduc;
	t_node	*new_root;

	left_reduc = 999;
	right_reduc = 999;
	new_root = NULL;
	if (node->left)
		left_reduc = node->left->reduc;
	if (node->right)
		right_reduc = node->right->reduc;
	if (left_reduc <= right_reduc)
	{
		node->left->left = node->right;
		new_root = node->left;
	}
	else
	{
		node->right->left = node->left;
		new_root = node->right;
	}
	free(node);
	return (new_root);
}

static void	ms_visit_simplif(t_node *node, t_node *parent, int from)
{
	if (!node)
		return ;
	if (node->type == -1 && parent)
	{
		if (parent->left && parent->right)
		{
			node->left->left = node->right;
			if (from == LEFT)
				parent->left = node->left;
			else
				parent->right = node->left;
			free(node);
			node = parent;
		}
		else if (!parent->left || !parent->right)
		{
			parent->left = node->left;
			parent->right = node->right;
			free(node);
			node = parent;
		}
	}
	ms_visit_simplif(node->left, node, LEFT);
	ms_visit_simplif(node->right, node, RIGHT);
}

static void	ms_visit_retype(t_node *node)
{
	if (!node)
		return ;
	if (node->type == 0)
	{
		if (node->reduc > R_CMD_NAME || node->reduc == -1)
			node->type = A_PARAM;
	}
	ms_visit_retype(node->left);
	ms_visit_retype(node->right);
}

t_node	*ms_simplify_tree(t_node *tree)
{
	while (tree->type == -1)
		tree = ms_promote_child(tree);
	ms_visit_simplif(tree, NULL, ROOT);
	ms_visit_retype(tree);
	return (tree);
}
