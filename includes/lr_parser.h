/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:18:13 by twagner           #+#    #+#             */
/*   Updated: 2021/10/29 14:21:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LR_PARSER_H
# define LR_PARSER_H
# include "minishell.h"
# include "token.h"

/*
** LR_PARSER DEFINES
*/
# define NB_TRANS 172
# define AUTOMATON "./srcs/grammar/automaton"
# define NO_ACTION -1
# define DEFAULT -1
# define SHIFT 0
# define REDUCE 1
# define ACCEPT 2

typedef enum e_rules
{
	AND_OR = 100,
	PIPE_SEQUENCE,
	SIMPLE_COMMAND,
	CMD_NAME,
	CMD_WORD,
	CMD_PREFIX,
	CMD_SUFFIX,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END,
	NEWLINE_LIST,
	LINEBREAK
}	t_rules;

/*
** LR_PARSER STRUCTURES
*/
typedef struct s_trans
{
	int	state;
	int	event;
	int	action;
	int	next;
	int	nb_reduce;
}		t_trans;

typedef struct s_stack
{
	int				type;
	int				state;
	void			*data;
	struct s_stack	*next;
}	t_stack;

/*
** LR_PARSER FUNCTIONS
*/
t_trans		**ms_init_state_machine(void);
void		ms_free_transitions(t_trans **trans);
t_stack		*ms_new_stack_item(void *content, int type, int state);
t_stack		*ms_pop_stack(t_stack **stack);
void		ms_add_front(t_stack **stack, t_stack *item);
void		ms_free_stack_item(t_stack *stack);
void		ms_free_stack(t_stack **stack);
int			ms_parser(t_token *tok_list, t_trans **trans);

#endif