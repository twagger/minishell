/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:58:18 by twagner           #+#    #+#             */
/*   Updated: 2022/01/07 15:59:30 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser2.h"

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
