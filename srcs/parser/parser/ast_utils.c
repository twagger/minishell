/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 15:54:53 by twagner           #+#    #+#             */
/*   Updated: 2021/11/01 21:01:04 by twagner          ###   ########.fr       */
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

void	ms_free_ast_builder(t_ast_builder **builder, int to_free)
{
	int	i;

	if (builder && *builder)
	{
		if ((*builder)->temp && (to_free == ALL || to_free == TEMP \
			|| to_free == TEMP_AND_RIGHT))
		{
			i = -1;
			while ((*builder)->temp[++i])
				free((*builder)->temp[i]);
		}
		if (to_free == ALL || to_free == LEFT)
			free((*builder)->left);
		if (to_free == ALL || to_free == RIGHT || to_free == TEMP_AND_RIGHT)
			free((*builder)->right);
		free(*builder);
	}
}

t_ast_builder	*ms_create_ast_builder(void)
{
	t_ast_builder	*new;

	new = (t_ast_builder *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->temp = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
