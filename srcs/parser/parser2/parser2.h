/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:55:55 by twagner           #+#    #+#             */
/*   Updated: 2022/01/07 08:44:32 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER2_H
# define PARSER2_H
# include "parser.h"

/*
** STACK
*/

t_stack	*ms_init_stack(void);
void	ms_clear_stack(t_stack *stack);
int		ms_push_input(t_stack **stack, t_token *input);
int		ms_push_reduction(t_stack **stack, int reduction);
int		ms_push_state(t_stack **stack, int state);

/*
** PARSING TABLE
*/

t_trans *ms_get_entry(t_token *input, t_trans **parsing_table, int state);

/*
** INPUT
*/

void	ms_clear_input(t_token *input);

/*
** TREE
*/

void	ms_clear_tree(t_node **node);

#endif