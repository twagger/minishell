/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:50:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 15:45:05 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
** HANDLE SPECIFIC INPUT (arrow keys, home, end, del)
*/

static int	ms_handle_escape_sequence(t_history **histo, char *seq, int *cpos)
{
	if (ft_strlen(seq) == 3)
	{
		ms_handle_move(histo, seq, cpos);
		ms_handle_history(histo, seq, cpos);
		ms_handle_delete(histo, seq, cpos);
	}
	if (ft_strlen(seq) == 4)
		ms_handle_delete(histo, seq, cpos);
	return (0);
}

/*
** HANDLE SIMPLE INPUT (simple char, backspace, new line)
*/


static int	ms_handle_simple_char(t_history **histo, char c, int *cpos)
{
	int	where;

	if (*cpos == (int)ft_strlen((*histo)->data))
		where = -1;
	else
		where = *cpos;
	if (ft_isprint(c))
	{
		++(*cpos);
		if (ms_add_char(histo, c, where) == ERROR)
			return (ERROR);
		ms_put_line((*histo)->data, *cpos);
	}
	else if (c == '\n')
	{
		ft_putchar_fd(c, 1);
		return (LINE_END);
	}
	else if (c == BACKSPACE && *cpos != 0)
	{
		--(*cpos);
		ms_handle_delete(histo, NULL, cpos);
		ms_put_line((*histo)->data, *cpos);
	}
	return (EXIT_SUCCESS);
}

/*
** READLINE
** Command line input with :
** - Prompt
** - Cursor movement
** - History
*/

char	*ms_readline(t_history **histo)
{
	char	c[11];
	int		ret;
	int		cpos;
	int		is_empty;

	cpos = 0;
	is_empty = 0;
	ft_putstr_fd(PROMPT, 1);
	tputs(tgetstr("sc", NULL), 0, ms_putchar);
	ms_histo_insert_front(histo, ms_histo_new(NULL), B_NEW);
	while (1)
	{
		ret = read(STDIN_FILENO, c, 10);
		if (ret == ERROR)
			break ;
		c[ret] = '\0';
		if (ret == 1)
		{
			ret = ms_handle_simple_char(histo, c[0], &cpos);
			if (ret == ERROR)
				return (NULL);
			if (ret == LINE_END)
				break ;
		}
		else if (ms_handle_escape_sequence(histo, c, &cpos) == ERROR)
			return (NULL);
	}
	if ((*histo)->type != B_NEW)
		(*histo)->type = B_HISTO_RESTORE;
	if ((*histo)->data)
		ms_histo_insert_front(histo, ms_histo_new(ft_strdup((*histo)->data)), B_HISTO);
	else
		is_empty = 1;
	ms_histo_clean(histo);
	/* display history */
	t_history *begin;
	while (*histo && (*histo)->previous)
		*histo = (*histo)->previous;
	begin = *histo;
	printf("\n------\n");
	while (*histo)
	{
		printf("T : %i\tH : %s\n", (*histo)->type, (*histo)->data);
		*histo = (*histo)->next;
	}
	printf("------\n");
	*histo = begin;
	/* end of display history */
	// ne pas renvoyer quelque chose si aucune commande
	if (is_empty)
		return (NULL);
	else if (*histo)
		return ((*histo)->data);
	return (NULL);
}
