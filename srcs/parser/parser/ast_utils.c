/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:54:53 by twagner           #+#    #+#             */
/*   Updated: 2021/11/11 15:55:54 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_visit_ast(t_node *node, int mode)
{
	if (!node)
		return ;
	if (mode == PRE_ORDER)
		printf("TYPE : %i\tDATA : %s\n", node->type, (char *)node->data);
	ms_visit_ast(node->left, mode);
	if (mode == IN_ORDER)
		printf("TYPE : %i\tDATA : %s\n", node->type, (char *)node->data);
	ms_visit_ast(node->right, mode);
	if (mode == POST_ORDER)
		printf("TYPE : %i\tDATA : %s\n", node->type, (char *)node->data);
}

void	ms_free_tree(t_node	*node)
{
	if (node)
	{
		if (node->left)
			ms_free_tree(node->left);
		if (node->right)
			ms_free_tree(node->right);
		if (!node->left && !node->right)
		{
			free(node->data);
			free(node);
		}
	}
}

t_node	*ms_new_node(void *data, int type, int reduc)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = data;
	new->type = type;
	new->reduc = reduc;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
