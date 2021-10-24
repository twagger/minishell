/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 11:04:45 by twagner           #+#    #+#             */
/*   Updated: 2021/10/23 09:47:45 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast.h"

t_node	*ms_create_node(void *data, int type)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->data = data;
	new->type = type;
	return (new);
}
