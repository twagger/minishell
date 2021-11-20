/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:31:32 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 15:23:39 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "minishell.h"

/*
** PARAMS
*/

# define PROMPT "\x1B[32mMinishell> \e[0m"
# define LINE_END -2
# define ESCAPE_SEQUENCE 27
# define BACKSPACE 127
# define ARROW_UP 65
# define ARROW_DOWN 66
# define ARROW_RIGHT 67
# define ARROW_LEFT 68
# define HOME 72
# define END 70
# define B_NEW 0
# define B_HISTO 1
# define B_HISTO_RESTORE 2

/*
** STRUCTURES
*/

typedef struct s_history
{
	int					type;
	char				*data;
	char				*saved_data;
	struct s_history	*previous;
	struct s_history	*next;
}						t_history;

/*
** FUNCTIONS
*/

/*
** raw mode
*/
int			ms_enable_raw_mode(struct termios *orig_termios);
int			ms_disable_raw_mode(struct termios *orig_termios);

/*
** readline
*/
char		*ms_readline(t_history **histo);
char		ms_ctrl_key(char key);
int			ms_putchar(int i);
int			ms_handle_move(t_history **histo, char *seq, int *cpos);
int			ms_handle_history(t_history **histo, char *seq, int *cpos);
int			ms_handle_delete(t_history **histo, char *seq, int *cpos);
void		ms_put_line(char *buffer, int cpos);
int			ms_add_char(t_history **histo, char c, int where);
char		*ms_del_char(t_history **histo, int index);

/*
** history
*/
t_history	*ms_histo_new(char *data);
void		ms_histo_insert_front(t_history **histo, t_history *insert, \
			int type);
void		ms_histo_del_one(t_history **histo, t_history **begin);
void		ms_histo_clear(t_history *histo);
void		ms_histo_clean(t_history **histo);

#endif