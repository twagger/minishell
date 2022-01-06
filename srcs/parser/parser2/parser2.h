/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:55:55 by twagner           #+#    #+#             */
/*   Updated: 2022/01/06 23:12:23 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER2_H
# define PARSER2_H
# include "parser.h"

typedef enum e_return_codes
{
	RET_CLEAR_TREE = -2,
	RET_OK = 0
}	t_return_codes;


/*
** STACK
*/

t_stack	*ms_init_stack(void);
void	ms_clear_stack(t_stack *stack);

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