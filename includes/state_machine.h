/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:18:13 by twagner           #+#    #+#             */
/*   Updated: 2021/10/24 11:33:01 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_MACHINE_H
# define STATE_MACHINE_H
# include "minishell.h"
# include "token.h"

/*
** STATE MACHINE DEFINES
*/
# define NO_ACTION -1
# define SHIFT 0
# define REDUCE 1
# define ACCEPT 2

typedef enum e_rules
{
	100 AND_OR = 100,
	101 PIPE_SEQUENCE,
	102 SIMPLE_COMMAND,
	103 CMD_NAME,
	104 CMD_WORD,
	105 CMD_PREFIX,
	106 CMD_SUFFIX,
	107 IO_REDIRECT,
	108 IO_FILE,
	109 FILENAME,
	110 IO_HERE,
	111 HERE_END,
	112 NEWLINE_LIST,
	113 LINEBREAK
} 	e_rules;

/*
** STATE MACHINE STRUCTURES
*/
typedef struct s_transition
{
    int state;
    int event;
    int action;
	int	next;
} 		t_transition;

typedef struct s_state
{
	int				num;
	t_transition	**actions;
	t_transition	**gotos;
}					t_state;

/*
** PARSING TREE FUNCTIONS
*/
t_state	*ms_new_state(int num, t_transition **actions, t_transition **gotos);
t_transition *ms_new_transition(int state, int event, int action, int next);
// init state machine
// free state machine
#endif