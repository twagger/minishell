/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:50:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 12:33:49 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	ms_handle_escape_sequence(\
	char **buffer, char *seq, t_history **histo, int *cpos)
{
	if (ft_strlen(seq) == 3)
	{
		ms_handle_move(buffer, seq, cpos);
		ms_handle_history(buffer, seq, histo, cpos);
		ms_handle_delete(buffer, seq, cpos);
	}
	if (ft_strlen(seq) == 4)
		ms_handle_delete(buffer, seq, cpos);
	return (0);
}

static int	ms_handle_simple_char(char **buffer, char c, int *cpos)
{
	int where;

	if (*cpos == (int)ft_strlen(*buffer))
		where = -1;
	else
		where = *cpos;	
	if (ft_isprint(c))
	{
		++(*cpos);
		if (ms_add_char(buffer, c, where) == ERROR)
			return (ERROR);
		ms_put_line(*buffer, *cpos);
	}
	else if (c == '\n')
	{
		ft_putchar_fd(c, 1);
		return (LINE_END);
	}
	else if (c == BACKSPACE && *cpos != 0)
	{
		--(*cpos);
		ms_handle_delete(buffer, NULL, cpos);
		ms_put_line(*buffer, *cpos);
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
	ms_histo_rewind(histo);
	ms_histo_insert_front(histo, ms_histo_new(ft_strdup(buffer)), B_HISTO);
	return (buffer);
}