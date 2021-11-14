/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:50:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/14 11:48:58 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	ms_handle_move(char **buffer, char *seq, int *cpos)
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

static int	ms_handle_history(\
	char **buffer, char *seq, t_history **histo, int *cpos)
{
	if (seq[1] == 91 && seq[2] == 65)
	{
		// add current buffer in history (last)
		ms_histo_insert_front(histo, ms_histo_new(ft_strdup(*buffer)));
		// clear buffer
		*buffer = NULL;
		// clear current line
		tputs(tgetstr("dl", NULL), 0, ms_putchar);
		// put the prompt and restore cursor position
		ft_putstr_fd("\x1B[32mMinishell> \e[0m", 1);
		tputs(tgetstr("rc", NULL), 0, ms_putchar);
		// buffer = previous
		if ((*histo)->next)
			*buffer = (*histo)->next->data;
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

static int	ms_handle_escape_sequence(\
	char **buffer, char *seq, t_history **histo, int *cpos)
{
	int	line_len;

	line_len = ft_strlen(*buffer);
	if (ft_strlen(seq) == 3)
	{
		ms_handle_move(buffer, seq, cpos);
		ms_handle_history(buffer, seq, histo, cpos);
	}
	return (0);
}

static int	ms_handle_simple_char(char **buffer, char c, int *cpos)
{
	if (ft_isprint(c))
	{
		++(*cpos);
		ft_putchar_fd(c, 1);
		if (ms_add_char(buffer, c) == ERROR)
			return (ERROR);
	}
	else if (c == '\n')
	{
		ft_putchar_fd(c, 1);
		return (LINE_END);
	}
	else if (c == BACKSPACE)
	{
		--(*cpos);
		ft_putchar_fd('*', 1);
	}
	return (EXIT_SUCCESS);
}

char	*ms_readline(const char *prompt, t_history **histo)
{
	char	*buffer;
	char	c[11];
	int		ret;
	int		cpos;

	buffer = NULL;
	cpos = 0;
	ft_putstr_fd((char *)prompt, 1);
	tputs(tgetstr("sc", NULL), 0, ms_putchar);
	while (1)
	{
		ret = read(STDIN_FILENO, c, 10);
		if (ret == ERROR)
			break ;
		c[ret] = '\0';
		if (ret == 1)
		{
			ret = ms_handle_simple_char(&buffer, c[0], &cpos);
			if (ret == ERROR)
				return (NULL);
			if (ret == LINE_END)
				break ;
		}
		else if (ms_handle_escape_sequence(&buffer, c, histo, &cpos) == ERROR)
			return (NULL);
	}
	ms_histo_insert_front(histo, ms_histo_new(ft_strdup(buffer)));
	return (buffer);
}