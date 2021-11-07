/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:22:47 by twagner           #+#    #+#             */
/*   Updated: 2021/11/07 12:08:30 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ms_buffer_add_back(t_ast_builder **builder, t_node *new)
{
	int		i;
	t_node	**new_buf;

	i = 0;
	while ((*builder)->buffer[i])
		++i;
	new_buf = (t_node **)malloc(sizeof(*new_buf) * (i + 2));
	if (!new_buf)
		return (ERROR);
	new_buf[i + 1] = NULL;
	new_buf[i] = new;
	while (--i >= 0)
		new_buf[i] = (*builder)->buffer[i];
	free((*builder)->buffer);
	(*builder)->buffer = new_buf;
	return (EXIT_SUCCESS);
}

t_node	*ms_buffer_remove(t_ast_builder **builder, int to_remove)
{
	int		i;
	int		j;
	t_node	*popped;
	t_node	**new_buf;

	i = 0;
	while ((*builder)->buffer[i])
		++i;
	new_buf = (t_node **)malloc(sizeof(*new_buf) * i);
	if (!new_buf)
		return (NULL);
	new_buf[i - 1] = NULL;
	j = -1;
	i = -1;
	while ((*builder)->buffer[++j])
	{
		if (j != to_remove)
			new_buf[++i] = (*builder)->buffer[j];
	}
	popped = (*builder)->buffer[to_remove];
	free((*builder)->buffer);
	(*builder)->buffer = new_buf;
	return (popped);
}

void	ms_free_ast_builder(t_ast_builder **builder, int to_free)
{
	int	i;

	if (builder && *builder)
	{
		if ((*builder)->buffer && (to_free == ALL || to_free == BUFFER))
		{
			i = -1;
			while ((*builder)->buffer[++i])
				ms_free_tree((*builder)->buffer[i]);
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
