/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:54:53 by twagner           #+#    #+#             */
/*   Updated: 2022/01/04 14:02:00 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ms_visit_ast(t_node *node, int mode)
{
	if (!node)
		return ;
	if (mode == PRE_ORDER)
	{
		if (node->type != -1)
			printf("TYPE : %i\tDATA : %s\n", node->type, (char *)node->data);
	}
	ms_visit_ast(node->left, mode);
	if (mode == IN_ORDER)
	{
		if (node->type != -1)
			printf("TYPE : %i\tDATA : %s\n", node->type, (char *)node->data);
	}
	ms_visit_ast(node->right, mode);
	if (mode == POST_ORDER)
	{
		if (node->reduc == R_IO_REDIRECT)
			printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_REDIRECT");
		if (node->reduc == R_IO_FILE)
			printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_FILE");
		if (node->reduc == R_IO_HERE)
			printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_HERE");
		if (node->type != -1 && node->type != -2)
			printf("TYPE : %i\tDATA : %s\tREDUC : %i\n", node->type, (char *)node->data, node->reduc);
		if (node->reduc == R_PIPE_SEQUENCE && node->type == ROOT)
			printf("TYPE : %i\tDATA : %s\n", node->type, "LAST SIMPLE COMMAND");
		else if (node->reduc == R_PIPE_SEQUENCE)
			printf("TYPE : %i\tDATA : %s\n", node->type, "SIMPLE COMMAND");
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

static void	ms_visit_fix_types(t_node *node)
{
	if (!node)
		return ;
	ms_visit_fix_types(node->left);
	ms_visit_fix_types(node->right);
	if (node->type == 0)
	{
		if (node->reduc > R_CMD_WORD || node->reduc == -1)
			node->type = A_PARAM;
	}
}

t_node	*ms_fix_param_types(t_ast_builder *builder)
{
	t_node	*ast;

	if (builder->ast && builder->ast->type == -1)
		builder->ast->type = ROOT;
	ms_visit_fix_types(builder->ast);
	ast = builder->ast;
	free(builder->buffer);
	free(builder);
	return (ast);
}
