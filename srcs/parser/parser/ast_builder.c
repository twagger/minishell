/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:04:45 by twagner           #+#    #+#             */
/*   Updated: 2021/11/02 15:32:01 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "ast.h"

static int	ms_get_ast_type(int type, int reduction)
{
	if (type == T_WORD)
	{
		if (reduction == R_CMD_NAME)
			return (A_CMD);
		if (reduction == R_CMD_WORD)
			return (A_OPE);
		if (reduction == R_FILENAME)
			return (A_FILE);
		if (reduction == R_HERE_END)
			return (A_HERE);
	}
	if (type > 3)
		return (type);
	return (ERROR);
}

static int	ms_build_action(t_stack **popped, int reduction)
{
	int	nb_popped;
	int	terminal_index;

	nb_popped = 0;
	terminal_index = -1;
	while (popped[nb_popped])
	{
		if (popped[nb_popped]->type < 100)
			terminal_index = nb_popped;
		++nb_popped;
	}
	if (nb_popped == 1 && popped[0]->type < 100)
		return (B_PUT_TO_BUFFER);
	if (nb_popped == 1 && popped[0]->type >= 100 && (reduction == R_AND_OR \
		|| reduction == R_PIPE_SEQUENCE))
		return (B_SWITCH_BRANCH);
	if (nb_popped > 1 && terminal_index != -1)
		return (B_BUFFER_THEN_RULE + terminal_index);
	if (nb_popped > 1 && terminal_index == -1)
		return (B_APPLY_RULE);
	return (B_DO_NOTHING);
}

static int	ms_stack_to_buffer(\
	t_stack	*item, int reduction, t_ast_builder **builder)
{
	t_node	*new;

	(void)builder;
	new = (t_node *)malloc(sizeof(*new));
	if (!new)
		return (ERROR);
	new->type = ms_get_ast_type(item->type, reduction);
	new->data = ft_strdup(item->data);
	if (!new->data)
	{
		free(new);
		return (ERROR);
	}
	new->left = (*builder)->buffer;
	(*builder)->buffer = new;
	free(item->data);
	free(item);
	return (EXIT_SUCCESS);
}

void	ms_apply_rule(t_ast_builder **builder, int reduction)
{
	t_node	*next;
	int		curr_branch;

	curr_branch = (*builder)->current_branch;
	if (reduction == R_AND_OR || reduction == R_PIPE_SEQUENCE)
	{
		(*builder)->buffer->left = (*builder)->branch[LEFT];
		(*builder)->buffer->right = (*builder)->branch[RIGHT];
		(*builder)->branch[LEFT] = (*builder)->buffer;
		(*builder)->buffer = NULL;
		(*builder)->branch[RIGHT] = NULL;
	}
	else if (reduction == R_SIMPLE_COMMAND)
	{
		while ((*builder)->buffer)
		{
			next = (*builder)->buffer->left;
			(*builder)->buffer->left = (*builder)->branch[curr_branch];
			(*builder)->branch[curr_branch] = (*builder)->buffer;
			(*builder)->buffer = next;
		}
	}
	else if (reduction == R_CMD_PREFIX)
	{
		
	}
	else if (reduction == R_CMD_SUFFIX)
	{
		
	}
	else if (reduction == R_IO_REDIRECT)
	{
		
	}
	else if (reduction == R_IO_FILE)
	{
		
	}
	else if (reduction == R_HERE_END)
	{
		
	}
}

int	ms_ast_builder(t_ast_builder **builder, t_stack **popped, int reduction)
{
	int	res;

	res = ms_build_action(popped, reduction);
	if (res == B_PUT_TO_BUFFER)
	{
		if (ms_stack_to_buffer(popped[0], reduction, builder) == ERROR)
			return (ERROR);
	}
	else if (res == B_SWITCH_BRANCH)
	{
		if ((*builder)->current_branch == RIGHT)
			(*builder)->current_branch = LEFT;
		else
			(*builder)->current_branch = RIGHT;
	}
	else if (res >= B_APPLY_RULE)
		ms_apply_rule(builder, reduction);
	else if (res >= B_BUFFER_THEN_RULE)
	{
		if (ms_stack_to_buffer(popped[100 - res], reduction, builder) == ERROR)
			return (ERROR);
		ms_apply_rule(builder, reduction);
	}
	return (EXIT_SUCCESS);
}
