/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:04:45 by twagner           #+#    #+#             */
/*   Updated: 2021/11/07 10:26:19 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ast.h"

/*
** BUFFER THE TERM
** Put the popped term in the stack until it is reduced and can join the tree
*/

static int	ms_stack_to_buffer(\
	t_stack	*item, int reduction, t_ast_builder **builder)
{
	t_node	*new;
	t_node	**new_buf;

	new = ms_create_node(ft_strdup(item->data), item->type, reduction);
	if (!new || (new && !new->data))
		return (ERROR);
	ms_buffer_add_back(&(*builder)->buffer, new);
	if (!(*builder)->buffer)
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
	int		i;

	i = -1;
	while ((*builder)->buffer[++i])
	{
		if ((*builder)->buffer[i]->reduc == reduc)
		{
			if (action == KEEP)
				return ((*builder)->buffer[i]);
			else if (action == POP)
				return (ms_buffer_remove(&(*builder)->buffer, i));
		}
	}
	if ((*builder)->ast->reduc == reduc)
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
	int		i;
	t_node	*node;
	t_node	*child;

	
	if (nb == 1)
	{
		node = ms_get_popped(builder, popped[0]->type, KEEP);
		if (!node)
			return (ERROR);
		node->reduc = reduction;
		return (EXIT_SUCCESS);
	}
	node = ms_create_node(NULL, -1, reduction);
	if (!node)
		return (ERROR);
	i = -1;
	while (++i < nb)
	{
		if (popped[i]->type >= 100)
			child = ms_get_popped(builder, popped[i]->type, POP);
		else
			child = ms_create_node(ft_strdup(popped[i]->data), popped[i]->type, -1);
		if (!child)
			return (ERROR);
		if (i == 0)
			node->right = child;
		if (i == 1 && nb == 2)
			node->left = child;
		if (i == 1 && nb == 3)
		{
			child->right = node->right;
			child->reduc = reduction;
			free(node);
			node = child;
		}
		if (i == 2)
			node->left = child;
	} // attach the tree to the ast if possible or let it in buffer
	if (!(*builder)->ast || ((*builder)->ast && (*builder)->ast == node->left))
		(*builder)->ast = node;
	else
	{
		ms_buffer_add_back(&(*builder)->buffer, node);
		if (!(*builder)->buffer)
			return (ERROR);
	}
	return (EXIT_SUCCESS);
}

/*
** SIMPLIFY THE TREE
** This function simplifies the tree by removing useless nodes and promoting
** and flagging operator nodes
*/

static int	ms_simplify_tree(t_ast_builder **builder)
{
	(void)builder;
	return (0);
}

/*
** BUILDER
** Get a list of popped terms (terminal or not) and a reduction code and 
** build a binary tree from bottom - left to top.
*/

int	ms_ast_builder(t_ast_builder **builder, t_stack **popped, int reduction)
{
	int	nb;

	nb = 0;
	while (popped[nb])
		++nb;
	if (nb == 1 && popped[0]->type < 100)
	{
		if (ms_stack_to_buffer(popped[0], reduction, builder) == ERROR)
			return (ERROR);
	}
	else
	{
		if (ms_apply_reduction(builder, popped, reduction, nb) == ERROR)
			return (ERROR);
		if (ms_simplify_tree(builder) == ERROR)
			return (ERROR);
	}
	return (EXIT_SUCCESS);
}
