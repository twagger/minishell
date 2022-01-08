/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:58:18 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 14:21:13 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** CLEAR INPUT
** At the end of the parser or if an error occurs during the parsing.
*/

void	ms_clear_input(t_token *input)
{
	t_token	*next;

	while (input)
	{
		next = input->next;
		free(input->value);
		free(input);
		input = next;
	}
}

/*
** CLEAR TREE
** At the end of the parser or if an error occurs during the parsing.
*/

void	ms_clear_tree(t_node **node)
{
	if (*node)
	{
		if ((*node)->left)
			ms_clear_tree(&(*node)->left);
		if ((*node)->right)
			ms_clear_tree(&(*node)->right);
		if (!(*node)->left && !(*node)->right)
		{
			free((*node)->data);
			free((*node));
			*node = NULL;
		}
	}
}

/*
** PARSER CLEANING
*/

void	ms_parser_cleaning(\
	t_node **tree, t_stack *stack, t_token *input, int ret)
{
	if (ret == ERROR)
		ms_clear_tree(tree);
	ms_clear_stack(stack);
	ms_clear_input(input);
}

/*
** TREE TYPE FIXING
*/

void	ms_visit_ast(t_node *node)
{
	if (!node)
		return ;
	ms_visit_ast(node->left);
	ms_visit_ast(node->right);
	if (node->reduc == R_SIMPLE_COMMAND)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_SIMPLE_COMMAND");
	if (node->reduc == R_CMD_NAME)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_NAME");
	if (node->reduc == R_CMD_WORD)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_WORD");
	if (node->reduc == R_CMD_PREFIX)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_PREFIX");
	if (node->reduc == R_CMD_SUFFIX)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_CMD_SUFFIX");
	if (node->reduc == R_IO_REDIRECT)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_REDIRECT");
	if (node->reduc == R_IO_FILE)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_FILE");
	if (node->reduc == R_FILENAME)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_FILENAME");
	if (node->reduc == R_IO_HERE)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_IO_HERE");
	if (node->reduc == R_HERE_END)
		printf("TYPE : %i\tDATA : %s\n", node->type, "R_HERE_END");
	if (node->type != -1 && node->type != -2)
		printf("TYPE : %i\tDATA : %s\tREDUC : %i\n", node->type, (char *)node->data, node->reduc);
	if (node->reduc == R_PIPE_SEQUENCE && node->type == ROOT)
		printf("TYPE : %i\tDATA : %s\n", node->type, "LAST SIMPLE COMMAND");
	else if (node->reduc == R_PIPE_SEQUENCE)
		printf("TYPE : %i\tDATA : %s\n", node->type, "SIMPLE COMMAND");
}

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
