/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:35:57 by twagner           #+#    #+#             */
/*   Updated: 2021/10/26 17:19:48 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lr_parser.h"

/*
** LR Parser
** - Etat courant = 0
** - regarder le premier mot de la liste chainee des tokens (input)
** - regarder si le mot est defini comme "event" sur l'etat courant
** - si oui, realiser l'action associee et changer d'etat
** - lorsqu'on fait une reduction, revenir a l'etat d'avant pour savoir ou aller ensuite
** - lorsqu'on fait une reduction, creer un noeud de la branche du parsing tree
** 	> On doit pouvoir creer l'ast directement avec de bonnes regles ici
*/

/*
** Search in the transitions on the current state the one matching the token
** as the event and return the transition num in the transition array.
** If the token is not matching, that means that the grammar is not respected.
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

int ms_shift(t_token **tok_list, t_stack **stack)
{
	t_stack	*curr;
	t_token	*curr_tok;
	
	curr_tok = *tok_list;
	curr = ms_new_stack_item(ft_strdup(curr_tok->value), curr_tok->type);
	if (!curr)
		return (ERROR);
	ms_add_front(stack, curr);
	*tok_list = (*tok_list)->next;
	free(curr_tok->value);
	free(curr_tok);
	return (EXIT_SUCCESS);
}

int	ms_reduce(t_stack **stack, t_trans **table, int	num_trans)
{
	int		i;
	t_stack	*popped;
	t_stack	*reduction;
	t_stack	*begin;
	
	begin = *stack;
	while (*stack)
	{
		printf("%i | BEFORE | STACK : %i - %s\n", num_trans, (*stack)->type, (*stack)->data);
		*stack = (*stack)->next;
	}
	*stack = begin;
	i = -1;
	while (++i < table[num_trans]->nb_reduce)
	{
		popped = ms_pop_stack(stack);
		free(popped);
		popped = NULL;
	}
	reduction = ms_new_stack_item(NULL, table[num_trans]->next);
	if (!reduction)
		return (ERROR);
	ms_add_front(stack, reduction);
	begin = *stack;
	while (*stack)
	{
		printf("%i | AFTER | STACK : %i - %s\n", num_trans, (*stack)->type, (*stack)->data);
		*stack = (*stack)->next;
	}
	*stack = begin;
	return (0);
}

int	ms_lr_parse(int state, t_token *input, t_stack *stack, t_trans **table)
{
	int	num_trans;

	if (!input)
		return (0);
	num_trans = ms_match_token(input->type, state, table);
	if (num_trans == ERROR)
		return (ERROR);
	if (table[num_trans]->action == SHIFT)
	{
		if (ms_shift(&input, &stack) == ERROR)
			return (ERROR);
		if (ms_lr_parse(table[num_trans]->next, input, stack, table) == ERROR)
			return (ERROR);
	}
	else if (table[num_trans]->action == REDUCE)
	{
		if (ms_reduce(&stack, table, num_trans) == ERROR)
			return (ERROR);
		return (0);
	}
	num_trans = ms_match_token(stack->type, state, table);
	printf("TOK : %i - STATE : %i - NEXT STATE  : %i\n", stack->type, state, table[num_trans]->next);
	if (ms_lr_parse(table[num_trans]->next, input, stack, table) == ERROR)
		return (ERROR);
	return (0);
}

int	ms_parser(t_token *tok_list, t_trans **trans)
{
	if (ms_lr_parse(0, tok_list, NULL, trans) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}
