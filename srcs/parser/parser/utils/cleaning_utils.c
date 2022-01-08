/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:58:18 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 14:44:18 by twagner          ###   ########.fr       */
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
		ms_clear_tree(&(*node)->left);
		ms_clear_tree(&(*node)->right);
		if (!(*node)->left && !(*node)->right)
		{
			free((*node)->data);
			free(*node);
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
