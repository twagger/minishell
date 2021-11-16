/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:11:40 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 12:33:08 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	ms_handle_move(char **buffer, char *seq, int *cpos)
{
	if (seq[1] == 91 && seq[2] == 67 && (int)ft_strlen(*buffer) > *cpos)
	{
		tputs(tgetstr("nd", NULL), 0, ms_putchar);
		++(*cpos);
	}
	if (seq[1] == 91 && seq[2] == 68 && *cpos > 0)
	{
		tputs(tgetstr("le", NULL), 0, ms_putchar);
		--(*cpos);
	}
	if (seq[1] == 91 && seq[2] == 70 && (int)ft_strlen(*buffer) > *cpos)
	{
		tputs(tgoto(tgetstr("RI", NULL), 0, \
			(*cpos - ft_strlen(*buffer)) * -1), 0, ms_putchar);
		*cpos = (int)ft_strlen(*buffer);
	}
	if (seq[1] == 91 && seq[2] == 72)
	{
		tputs(tgetstr("rc", NULL), 0, ms_putchar);
		*cpos = 0;
	}
	return (0);
}

int	ms_handle_history(char **buffer, char *seq, t_history **histo, int *cpos)
{
	if (seq[1] == 91 && seq[2] == 65)
	{
		// add current buffer in history (last)
		if (!ms_is_new_in_histo(histo))
			ms_histo_insert_front(histo, ms_histo_new(ft_strdup(*buffer)), B_NEW);
		// clear current line
		tputs(tgetstr("dl", NULL), 0, ms_putchar);
		// put the prompt and restore cursor position
		ft_putstr_fd("\x1B[32mMinishell> \e[0m", 1);
		tputs(tgetstr("rc", NULL), 0, ms_putchar);
		// buffer = previous
		if ((*histo)->next)
		{
			*buffer = (*histo)->next->data;
			*histo = (*histo)->next;
		}
		else
			*buffer = (*histo)->data;
		// display buffer
		ft_putstr_fd(*buffer, 1);
		*cpos = ft_strlen(*buffer);
	}
	if (seq[1] == 91 && seq[2] == 66)
		tputs(tgetstr("do", NULL), 0, ms_putchar);
	return (0);
}

int	ms_handle_delete(char **buffer, char *seq, int *cpos)
{
	if (seq == NULL || (seq[1] == 91 && seq[2] == 51 && seq[3] == 126))
	{
		if (*cpos != (int)ft_strlen(*buffer))
		{
			*buffer = ms_del_char(buffer, *cpos);
			if (!*buffer)
				return (ERROR);
		}
	}
	return (0);
}
