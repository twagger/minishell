/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 14:44:01 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 14:44:23 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** TREE TYPE FIXING
*/

static void	ms_visit_fix_types(t_node *node)
{
	if (!node)
		return ;
	if (node->reduc == R_FILENAME)
		node->right->type = A_FILE;
	if (node->reduc == R_HERE_END)
		node->right->type = A_LIMITER;
	if (node->reduc > R_CMD_WORD)
	{
		if (node->left && node->left->type == A_CMD)
			node->left->type = A_PARAM;
		if (node->right && node->right->type == A_CMD)
			node->right->type = A_PARAM;
	}
	ms_visit_fix_types(node->left);
	ms_visit_fix_types(node->right);
}

t_node	*ms_fix_param_types(t_node *tree)
{
	if (tree && tree->type == -1)
		tree->type = ROOT;
	ms_visit_fix_types(tree);
	return (tree);
}
