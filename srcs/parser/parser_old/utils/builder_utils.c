/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:22:47 by twagner           #+#    #+#             */
/*   Updated: 2022/01/04 15:32:17 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ms_build_subtree(t_ast_builder **builder, t_stack *term, t_node **node)
{
	int		i;
	t_node	*child;
	t_node	*init;

	i = 0;
	init = *node;
	while (term)
	{
		if (term->type >= 100)
			child = ms_get_popped(builder, term->type, POP);
		else
			child = ms_new_node(ft_strdup(term->data), term->type, -1);
		if (!child)
			return (ERROR);
		if (i == 0)
			(*node)->right = child;
		else
			(*node)->left = child;
		if (i == 1 && term->next)
			*node = (*node)->left;
		term = term->next;
		++i;
	}
	*node = init;
	return (EXIT_SUCCESS);
}

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

int	ms_init_ast_builder(t_ast_builder **builder)
{
	*builder = (t_ast_builder *)malloc(sizeof(**builder));
	if (!*builder)
		return (ERROR);
	(*builder)->buffer = (t_node **)malloc(sizeof(t_node *));
	if (!(*builder)->buffer)
	{
		free(*builder);
		return (ERROR);
	}
	(*builder)->buffer[0] = NULL;
	(*builder)->ast = NULL;
	return (EXIT_SUCCESS);
}
