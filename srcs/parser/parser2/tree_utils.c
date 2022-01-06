/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:59:05 by twagner           #+#    #+#             */
/*   Updated: 2022/01/06 23:12:13 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser2.h"

// add tree

// create node

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