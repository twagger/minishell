/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:54:53 by twagner           #+#    #+#             */
/*   Updated: 2021/11/02 15:18:28 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ms_free_node(t_node *node)
{
	if (node)
	{
		free(node->data);
		free(node);
	}
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
			ms_free_node(node);
	}
}

t_node	*ms_create_node(void *data, int type)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = data;
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	ms_free_ast_builder(t_ast_builder **builder, int to_free)
{
	t_node	*next;

	if (builder && *builder)
	{
		if ((*builder)->buffer && (to_free == ALL || to_free == TEMP \
			|| to_free == TEMP_AND_RIGHT))
		{
			while ((*builder)->buffer)
			{
				next = (*builder)->buffer->left;
				ms_free_node((*builder)->buffer);
				(*builder)->buffer = next;
			}
		}
		if (to_free == ALL || to_free == LEFT)
			ms_free_tree((*builder)->branch[LEFT]);
		if (to_free == ALL || to_free == RIGHT || to_free == TEMP_AND_RIGHT)
			ms_free_tree((*builder)->branch[RIGHT]);
		free(*builder);
	}
}

t_ast_builder	*ms_create_ast_builder(void)
{
	t_ast_builder	*new;

	new = (t_ast_builder *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->current_branch = LEFT;
	new->buffer = NULL;
	new->branch[LEFT] = NULL;
	new->branch[RIGHT] = NULL;
	return (new);
}
