/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:11:40 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 15:42:03 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	ms_handle_move(char **buffer, char *seq, int *cpos)
{
	if (seq[1] == 91 && seq[2] == ARROW_RIGHT \
		&& (int)ft_strlen(*buffer) > *cpos)
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
		&& (int)ft_strlen(*buffer) > *cpos)
	{
		tputs(tgoto(tgetstr("RI", NULL), 0, \
			(*cpos - ft_strlen(*buffer)) * -1), 0, ms_putchar);
		*cpos = (int)ft_strlen(*buffer);
	}
	if (seq[1] == 91 && seq[2] == HOME)
	{
		tputs(tgetstr("rc", NULL), 0, ms_putchar);
		*cpos = 0;
	}
	return (0);
}

int	ms_handle_history(char **buffer, char *seq, t_history **histo, int *cpos)
{
	if (seq[1] == 91 && seq[2] == ARROW_UP)
	{
		if (!ms_is_new_in_histo(histo))
			ms_histo_insert_front(histo, ms_histo_new(ft_strdup(*buffer)), B_NEW);
		if ((*histo)->next)
		{
			*buffer = (*histo)->next->data;
			*histo = (*histo)->next;
		}
		else
			*buffer = (*histo)->data;
	}
	if (seq[1] == 91 && seq[2] == ARROW_DOWN)
	{
		if ((*histo)->previous)
		{
			*buffer = (*histo)->previous->data;
			*histo = (*histo)->previous;
		}
		else
			*buffer = (*histo)->data;
	}
	*cpos = ft_strlen(*buffer);
	ms_put_line(*buffer, *cpos);
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
