/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:18:13 by twagner           #+#    #+#             */
/*   Updated: 2021/10/30 14:37:17 by twagner          ###   ########.fr       */
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
# define ACTION 114
# define GOTO 58
# define AUTOMATON "./srcs/parser/parser/automaton"
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
t_trans	**ms_init_parsing_table(void);
void	ms_free_table(t_trans **trans);
t_stack	*ms_new_stack_item(void *content, int type, int state);
void	ms_pop_stack(t_stack **stack, int nb);
int		ms_add_front(t_stack **stack, t_stack *item);
void	ms_free_stack_item(t_stack *stack);
void	ms_free_stack(t_stack **stack);
int		ms_parser(t_token *tok_list, t_trans **table);

#endif