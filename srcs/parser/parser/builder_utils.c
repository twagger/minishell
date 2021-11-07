/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:22:47 by twagner           #+#    #+#             */
/*   Updated: 2021/11/07 10:56:30 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ms_buffer_add_back(t_node ***buffer, t_node *new)
{
	int		i;
	t_node	**new_buf;

	i = 0;
	while ((*buffer)[i])
		++i;
	new_buf = (t_node **)malloc(sizeof(*new_buf) * (i + 2));
	if (!new_buf)
	{
		**buffer = NULL;
		return ;
	}
	new_buf[i + 1] = NULL;
	new_buf[i] = new;
	while (--i >= 0)
		new_buf[i] = (*buffer)[i];
	while (**buffer)
	{
		ms_free_tree(**buffer);
		++(*buffer);
	}
}

t_node	*ms_buffer_remove(t_node ***buffer, int to_remove)
{
	int		i;
	t_node	*popped;
	t_node	**new_buf;

	i = 0;
	while ((*buffer)[i])
		++i;
	new_buf = (t_node **)malloc(sizeof(*new_buf) * i);
	if (!new_buf)
		return (ERROR);
	new_buf[--i] = NULL;
	while (--i >= 0)
	{
		if (i != to_remove)
			new_buf[i] = (*buffer)[i];
	}
	popped = (*buffer)[to_remove];
	while (**buffer)
	{
		ms_free_tree(**buffer);
		++(*buffer);
	}
	buffer = &new_buf;
	return (popped);
}

void	ms_free_ast_builder(t_ast_builder **builder, int to_free)
{
	if (builder && *builder)
	{
		if ((*builder)->buffer && (to_free == ALL || to_free == BUFFER))
		{
			while ((*builder)->buffer)
			{
				ms_free_tree((*builder)->buffer);
				++(*builder)->buffer;
			}
		}
		if (to_free == ALL || to_free == AST)
			ms_free_tree((*builder)->ast);
		if (to_free == ALL)
			free(*builder);
	}
}

t_ast_builder	*ms_create_ast_builder(void)
{
	t_ast_builder	*new;

	new = (t_ast_builder *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->buffer = (t_node **)malloc(sizeof(t_node *));
	if (!new->buffer)
	{
		free(new);
		return (NULL);
	}
	new->buffer[0] = NULL;
	new->ast = NULL;
	return (new);
}
