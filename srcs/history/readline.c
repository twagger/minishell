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

char	*ms_readline(const char *prompt, t_history **histo)
{
	char	c[11];
	int		ret;
	int		cpos;

	cpos = 0;
	ft_putstr_fd((char *)prompt, 1);
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
	ms_histo_clean(histo);

	/* display history */
	t_history *begin;
	if (*histo)
		while ((*histo)->previous)
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

	return ((*histo)->data);
}
