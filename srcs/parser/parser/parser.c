/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:35:57 by twagner           #+#    #+#             */
/*   Updated: 2022/01/04 15:44:04 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** LR Parser
** input : chained list of tokens from lexer
** table : table of transitions from automaton parsing
** stack : simple chained list
** output: parsing tree
*/

/*
** PARSING TABLE SEARCH
** Search for the right action or goto to do according to the current 
** state, stack and input
*/

static int	ms_get_table_index(\
	t_token *token, t_stack *stack, int s, t_trans **trans)
{
	int	i;
	int	def;
	int	tok_type;

	def = -1;
	tok_type = -1;
	if (token)
		tok_type = token->type;
	if (stack)
		tok_type = stack->type;
	i = -1;
	while (trans[++i])
	{
		if (trans[i]->state == s)
		{
			if (trans[i]->event == tok_type)
				return (i);
			else if (trans[i]->event == DEFAULT)
				def = i;
		}
	}
	if (def != -1)
		return (def);
	return (ERROR);
}

/*
** SHIFT
** Push the token on the top of the input into the stack
** and push the next state on the top of the stack
*/

static int	ms_shift(t_token **input, t_stack **stack, int state)
{
	t_stack	*s_tok;
	t_stack	*s_state;
	char	*tmp;

	if (!*input)
		return (ERROR);
	tmp = ft_strdup((*input)->value);
	if ((*input)->value && !tmp)
		return (ERROR);
	s_tok = ms_new_stack_item(tmp, (*input)->type, -1);
	if (!s_tok)
		return (ERROR);
	ms_add_front(stack, s_tok);
	s_state = ms_new_stack_item(NULL, -1, state);
	if (!s_state)
	{
		free(s_tok->data);
		free(s_tok);
		return (ERROR);
	}
	ms_add_front(stack, s_state);
	*input = (*input)->next;
	return (EXIT_SUCCESS);
}

/*
** REDUCE
** Pop the token and rules out of the stack and replace them with
** the corresponding production. Then add the next state on the 
** top of the stack
** FOR DEBUG, ADD THIS PART BEFORE ms_ast_builder :
**
**	printf("%i : ", reduction->type);
**	int i;
**	i = -1;
**	while (popped[++i])
**		printf("%i ", popped[i]->type);
**	printf("\n");
*/

static int	ms_reduce(\
	t_stack **stack, t_trans **table, int i_table, t_ast_builder **builder)
{
	int		num_state;
	t_stack	*reduction;
	t_stack	*state;
	t_stack	*popped;

	popped = ms_pop_stack(stack, table[i_table]->nb_reduce);
	if (!popped)
		return (ERROR);
	num_state = (*stack)->state;
	reduction = ms_new_stack_item(NULL, table[i_table]->next, -1);
	if (!reduction)
		return (ms_free_stack(popped, ERROR));
	ms_add_front(stack, reduction);
	i_table = ms_get_table_index(NULL, *stack, num_state, table);
	if (i_table == ERROR)
		return (ms_free_stack(popped, ERROR));
	state = ms_new_stack_item(NULL, -1, table[i_table]->next);
	if (!state)
		return (ms_free_stack(popped, ERROR));
	ms_add_front(stack, state);
	if (ms_ast_builder(builder, popped, reduction->type) == ERROR)
		return (ms_free_stack(popped, ERROR));
	ms_free_stack(popped, 0);
	return (EXIT_SUCCESS);
}

/*
** PARSE
** Read the input, find the right transition to apply from the parsing
** table for the current state, then shift or reduce until error or accept.
*/

static int	ms_lr_parse(\
	t_token *input, t_trans **table, t_stack **stack, t_ast_builder **builder)
{
	int		i_table;

	if (ms_add_front(stack, ms_new_stack_item(NULL, -1, 0)) == ERROR)
		return (ERROR);
	while (1)
	{
		i_table = ms_get_table_index(input, NULL, (*stack)->state, table);
		if (i_table == ERROR)
			return (ERROR);
		if (table[i_table]->action == SHIFT)
		{
			if (ms_shift(&input, stack, table[i_table]->next) == ERROR)
				return (ERROR);
		}
		else if (table[i_table]->action == REDUCE)
		{
			if (ms_reduce(stack, table, i_table, builder) == ERROR)
				return (ERROR);
		}
		else if (table[i_table]->action == ACCEPT)
			break ;
		else
			return (ERROR);
	}
	return (ACCEPT);
}

t_node	*ms_parser(t_token *tok_list, t_trans **table)
{
	t_token			*tok_end;
	t_stack			*stack;
	t_ast_builder	*builder;

	if (!tok_list || ms_init_ast_builder(&builder) == ERROR)
	{
		ms_free_tokens(tok_list);
		return (NULL);
	}
	stack = NULL;
	tok_end = ft_newtoken(NULL);
	if (tok_end)
	{
		ft_tokenadd_back(&tok_list, tok_end);
		if (ms_lr_parse(tok_list, table, &stack, &builder) == ERROR)
			builder->ast = NULL;
		else if (!builder->ast && builder->buffer[0])
			builder->ast = builder->buffer[0];
	}
	ms_free_tokens(tok_list);
	free(stack);
	return (ms_fix_param_types(builder));
}
