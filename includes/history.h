/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:31:32 by twagner           #+#    #+#             */
/*   Updated: 2021/11/13 16:04:04 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "minishell.h"

/*
** HISTORY PARAMS
*/

# define LINE_END -2
# define ESCAPE_SEQUENCE 27
# define BACKSPACE 127

/*
** HISTORY FUNCTIONS
*/

int		ms_enable_raw_mode(struct termios *orig_termios);
int		ms_disable_raw_mode(struct termios *orig_termios);

char	*ms_readline(const char *prompt);

char	ms_ctrl_key(char key);

#endif