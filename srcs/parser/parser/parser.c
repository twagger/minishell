/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:35:57 by twagner           #+#    #+#             */
/*   Updated: 2021/10/30 15:17:29 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lr_parser.h"
#include "token.h"

/*
** LR Parser
** input : chained list of tokens from lexer
** table : table of transitions from automaton parsing
** stack : simple chained list
** output: parsing tree
*/

static int	ms_get_trans(t_token *tok, t_stack *stack, int st, t_trans **trans)
{
	int	i;
	int	def;
	int	tok_type;

	def = -1;
	tok_type = -1;
	if (tok)
		tok_type = tok->type;
	if (stack)
		tok_type = stack->type;
	i = -1;
	while (trans[++i])
	{
		if (trans[i]->state == st)
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

	if (!*input)
		return (ERROR);
	s_tok = ms_new_stack_item(ft_strdup((*input)->value), (*input)->type, -1);
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
*/

static int	ms_reduce(t_stack **stack, t_trans **table, int num_trans)
{
	int		num_state;
	t_stack	*reduction;
	t_stack	*state;

	ms_pop_stack(stack, table[num_trans]->nb_reduce);
	num_state = (*stack)->state;
	reduction = ms_new_stack_item(NULL, table[num_trans]->next, -1);
	if (!reduction)
		return (ERROR);
	ms_add_front(stack, reduction);
	num_trans = ms_get_trans(NULL, *stack, num_state, table);
	if (num_trans == ERROR)
		return (ERROR);
	state = ms_new_stack_item(NULL, -1, table[num_trans]->next);
	if (!state)
		return (ERROR);
	ms_add_front(stack, state);
	printf("%i\n", reduction->type);
	return (EXIT_SUCCESS);
}

static int	ms_lr_parse(t_token *input, t_trans **table, t_stack **stack)
{
	int		i_trans;

	if (ms_add_front(stack, ms_new_stack_item(NULL, -1, 0)) == ERROR)
		return (ERROR);
	while (1)
	{
		i_trans = ms_get_trans(input, NULL, (*stack)->state, table);
		if (i_trans == ERROR)
			return (ERROR);
		if (table[i_trans]->action == SHIFT)
		{
			if (ms_shift(&input, stack, table[i_trans]->next) == ERROR)
				return (ERROR);
		}
		else if (table[i_trans]->action == REDUCE)
		{
			if (ms_reduce(stack, table, i_trans) == ERROR)
				return (ERROR);
		}
		else if (table[i_trans]->action == ACCEPT)
			break ;
		else
			return (ERROR);
	}
	return (ACCEPT);
}

int	ms_parser(t_token *tok_list, t_trans **table)
{
	t_token	*tok_end;
	t_stack	*stack;

	stack = NULL;
	tok_end = ft_newtoken(NULL);
	if (!tok_end)
		return (ERROR);
	ft_tokenadd_back(&tok_list, tok_end);
	if (ms_lr_parse(tok_list, table, &stack) == ERROR)
	{
		ms_free_stack(&stack);
		return (ERROR);
	}
	return (EXIT_SUCCESS);
}
