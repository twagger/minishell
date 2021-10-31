/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:54:53 by twagner           #+#    #+#             */
/*   Updated: 2021/10/31 09:25:13 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// ajouter free ast

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
