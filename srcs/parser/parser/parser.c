/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:35:57 by twagner           #+#    #+#             */
/*   Updated: 2021/10/29 15:07:18 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lr_parser.h"
#include "token.h"

/*
** LR Parser
**  input : chained listof tokens from lexer
** 	table : table of transitions from automaton parsing
**  stack : simple chained list
**  output: parsing tree
*/

// command to test : echo 'toto' > file && cat 'file'

int	ms_match_token(int token, int curr_state, t_trans **trans)
{
	int	i;
	int def;
	
	i = -1;
	def = -1;
	while (trans[++i])
	{
		if (trans[i]->state == curr_state)
		{
			if (trans[i]->event == token)
				return (i);
			else if (trans[i]->event == DEFAULT)
				def = i;
		}
	}
	if (def != -1)
		return (def);
	return (ERROR);
}

int ms_shift(t_token *tok, t_stack **stack, int state)
{
	t_stack	*new;
	char	*value;

	if (tok)
		value = ft_strdup(tok->value);
	else
		value = NULL;	
	new = ms_new_stack_item(value, tok->type, state);
	if (!new)
		return (ERROR);
	ms_add_front(stack, new);
	return (EXIT_SUCCESS);
}

int	ms_reduce(t_stack **stack, t_trans **table, int	num_trans)
{
	int		i;
	t_stack	*popped;
	t_stack	*state;
	t_stack	*reduction;
	t_trans	*trans;

	trans = table[num_trans];
	i = -1;
	state = ms_pop_stack(stack);
	while (++i < trans->nb_reduce)
	{
		popped = ms_pop_stack(stack);
		free(popped);
		popped = NULL;
	}
	ms_add_front(stack, state);
	reduction = ms_new_stack_item(NULL, trans->next, -1);
	if (!reduction)
		return (ERROR);
	ms_add_front(stack, reduction);
	printf("REDUCTION : %i\n", reduction->type);
	return (EXIT_SUCCESS);
}

int	ms_lr_parse(t_token *input, t_trans **table)
{
	t_token	*tok;
	int		state;
	int		num_trans;
	t_stack *stack;
	t_stack	*initial;

	stack = NULL;
	initial = ms_new_stack_item(NULL, -1, 0);
	if (!initial)
		return (ERROR);
	ms_add_front(&stack, initial);
	while (1)
	{
		state = stack->state;
		tok = input;
		num_trans = ms_match_token(tok->type, state, table);
		if (num_trans == ERROR)
			return (ERROR);
		if (table[num_trans]->action == SHIFT)
		{
			if (ms_shift(tok, &stack, -1) == ERROR)
				return (ERROR);
			if (ms_shift(NULL, &stack, table[num_trans]->next) == ERROR)
				return (ERROR);
			input = input->next;
		}
		else if (table[num_trans]->action == REDUCE)
		{
			if (ms_reduce(&stack, table, num_trans) == ERROR)
				return (ERROR);
		}
		else if (table[num_trans]->action == ACCEPT)
			break ;
		else
			return (ERROR);
	}
	return (ACCEPT);
}

int	ms_parser(t_token *tok_list, t_trans **trans)
{
	t_token	*tok_end;

	tok_end = ft_newtoken(NULL);
	if (!tok_end)
		return (ERROR);
	ft_tokenadd_back(&tok_list, tok_end);
	if (ms_lr_parse(tok_list, trans) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}
