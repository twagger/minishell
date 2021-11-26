/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:50:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/26 16:11:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/*
** HANDLE CONTROL KEYS IN INTERACTIVE MODE
** Ctrl + c / Ctrl + d / Ctrl + \
*/

static int	ms_handle_ctrl_keys(t_history **histo, char c)
{
	char	*tmp;
	
	if (c == ms_ctrl_key('c'))
	{
		ms_histo_clean(histo);
		return (1);
	}
	else if (c == ms_ctrl_key('d') && ft_strlen((*histo)->data) == 0)
	{
		tmp = (*histo)->data;
		(*histo)->data = ft_strdup("exit");
		printf("exit\n");
		free(tmp);
		return (2);
	}
	else
		return (0);
}

/*
** HANDLE SPECIFIC INPUT
** arrow keys, home, end, del
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
** HANDLE SIMPLE INPUT
** simple char, backspace, new line
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
		ms_insert_char(c);
	}
	else if (c == '\n')
	{
		if (ft_strlen((*histo)->data))
			ft_putchar_fd('\n', 1);
		return (LINE_END);
	}
	else if (c == BACKSPACE && *cpos != 0)
	{
		--(*cpos);
		tputs(tgetstr("le", NULL), 0, ms_putchar);
		ms_handle_delete(histo, NULL, cpos);
	}
	return (EXIT_SUCCESS);
}

/*
** ADD CURRENT ENTRY TO HISTORY
** Add the current entry to history (if not NULL) and clean history
** Then return the right command line or NULL if nothing has been typed
** Add the following lines after ms_histo_clean to display history :
**
**	t_history *begin;
**	while (*histo && (*histo)->previous)
**		*histo = (*histo)->previous;
**	begin = *histo;
**	printf("\n------\n");
**	while (*histo)
**	{
**		printf("T : %i\tH : %s\n", (*histo)->type, (*histo)->data);
**		*histo = (*histo)->next;
**	}
**	printf("------\n");
**	*histo = begin;
*/

static char	*ms_add_to_history(t_history **histo)
{
	int	is_empty;

	is_empty = 0;
	if ((*histo)->type != B_NEW)
		(*histo)->type = B_HISTO_RESTORE;
	if ((*histo)->data)
		ms_histo_insert_front(histo, \
			ms_histo_new(ft_strdup((*histo)->data)), B_HISTO);
	else
		is_empty = 1;
	ms_histo_clean(histo);
	if (is_empty)
		return (NULL);
	else if (*histo)
		return ((*histo)->data);
	return (NULL);
}

/*
** INIT READLINE
** - Display prompt
** - Save cursor initial position and set cpos (cursor position) value
** - Initialize new history entry
*/

static void	ms_init_readline(t_history **histo, int *cpos)
{
	*cpos = 0;
	ft_putstr_fd(PROMPT, 1);
	tputs(tgetstr("sc", NULL), 0, ms_putchar);
	ms_histo_insert_front(histo, ms_histo_new(NULL), B_NEW);
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
	char	c[10];
	int		ret;
	int		is_ctrl;
	int		cpos;

	ms_init_readline(histo, &cpos);
	while (1)
	{
		ret = read(STDIN_FILENO, c, 9);
		if (ret == ERROR)
			break ;
		is_ctrl = ms_handle_ctrl_keys(histo, c[0]);
		if (is_ctrl == CTRL_C)
			return (NULL);
		else if (is_ctrl == CTRL_D)
			return (ms_add_to_history(histo));
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
	return (ms_add_to_history(histo));
}
