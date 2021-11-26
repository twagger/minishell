/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:11:40 by twagner           #+#    #+#             */
/*   Updated: 2021/11/26 16:02:53 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
** HANDLE CURSOR MOVES
** -> / <- / <end> / <home>
*/

int	ms_handle_move(t_history **histo, char *seq, int *cpos)
{
	if (seq[1] == 91 && seq[2] == ARROW_RIGHT \
		&& (int)ft_strlen((*histo)->data) > *cpos)
	{
		tputs(tgetstr("nd", NULL), 0, ms_putchar);
		++(*cpos);
	}
	if (seq[1] == 91 && seq[2] == ARROW_LEFT && *cpos > 0)
	{
		tputs(tgetstr("le", NULL), 0, ms_putchar);
		--(*cpos);
	}
	if (seq[1] == 91 && seq[2] == END \
		&& (int)ft_strlen((*histo)->data) > *cpos)
	{
		tputs(tgoto(tgetstr("RI", NULL), 0, \
			(*cpos - ft_strlen((*histo)->data)) * -1), 0, ms_putchar);
		*cpos = (int)ft_strlen((*histo)->data);
	}
	if (seq[1] == 91 && seq[2] == HOME)
	{
		tputs(tgetstr("rc", NULL), 0, ms_putchar);
		*cpos = 0;
	}
	return (0);
}

/*
** HANDLE HISTORY DISPLAY
** <up arrow> / <down arrow>
*/

int	ms_handle_history(t_history **histo, char *seq, int *cpos)
{
	int	len;

	len = 0;
	if (*histo)
		len = ft_strlen((*histo)->data);
	if (seq[1] == 91 && seq[2] == ARROW_UP)
	{
		if ((*histo)->next)
			*histo = (*histo)->next;
	}
	if (seq[1] == 91 && seq[2] == ARROW_DOWN)
	{
		if ((*histo)->previous)
			*histo = (*histo)->previous;
	}
	if (seq[2] == ARROW_UP || seq[2] == ARROW_DOWN)
	{
		*cpos = ft_strlen((*histo)->data);
		ms_refresh_line((*histo)->data, len);
	}
	return (0);
}

/*
** HANDLE CHARACTER DELETION
** On an existing char * stored in history
*/

int	ms_handle_delete(t_history **histo, char *seq, int *cpos)
{
	if (seq == NULL || (seq[1] == 91 && seq[2] == 51 && seq[3] == 126))
	{
		if (*cpos != (int)ft_strlen((*histo)->data))
		{
			(*histo)->data = ms_del_char(histo, *cpos);
			if (!(*histo)->data)
				return (ERROR);
			if (ft_strlen((*histo)->data) == 0)
			{
				free((*histo)->data);
				(*histo)->data = NULL;
			}
			ms_delete_char();
		}
	}
	return (0);
}
