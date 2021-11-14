/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:31:32 by twagner           #+#    #+#             */
/*   Updated: 2021/11/14 11:40:34 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "minishell.h"

/*
** PARAMS
*/

# define LINE_END -2
# define ESCAPE_SEQUENCE 27
# define BACKSPACE 127

/*
** STRUCTURES
*/

typedef struct s_history
{
	void				*data;
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
char		*ms_readline(const char *prompt, t_history **histo);
char		ms_ctrl_key(char key);
int			ms_putchar(int i);
int			ms_add_char(char **buffer, char c);

/*
** history
*/
t_history	*ms_histo_new(void *data);
void		ms_histo_insert_front(t_history **histo, t_history *insert);
void		ms_histo_clear(t_history *histo);

#endif