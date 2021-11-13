/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:50:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/13 16:52:15 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	ms_putchar(int i)
{
	char c;

	c = (char)i;
	write(1, &c, 1);
	return (1);
}

static int	ms_add_char(char **buffer, char c)
{
	size_t	len;

	len = ft_strlen(*buffer);
	*buffer = ft_realloc(*buffer, len + 2);
	if (!buffer)
		return (ERROR);
	(*buffer)[len] = c;
	(*buffer)[len + 1] = '\0';
	return (EXIT_SUCCESS);
}

static int	ms_handle_escape_sequence(char **buffer, char *seq)
{
	int	line_len;

	line_len = ft_strlen(*buffer);
	if (ft_strlen(seq) == 3)
	{
		if (seq[1] == 91 && seq[2] == 65)
			tputs(tgetstr("up", NULL), 0, ms_putchar);
		if (seq[1] == 91 && seq[2] == 66)
			tputs(tgetstr("do", NULL), 0, ms_putchar);
		if (seq[1] == 91 && seq[2] == 67)
			tputs(tgetstr("nd", NULL), 0, ms_putchar);
		if (seq[1] == 91 && seq[2] == 68)
			tputs(tgetstr("le", NULL), 0, ms_putchar);
		if (seq[1] == 91 && seq[2] == 72)
			tputs(tgetstr("cr", NULL), 0, ms_putchar);
	}
	return (0);
}

static int	ms_handle_simple_char(char **buffer, char c)
{
	if (ft_isprint(c))
	{
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
		ft_putchar_fd('d', 1);
	}
	return (EXIT_SUCCESS);
}

char	*ms_readline(const char *prompt)
{
	char	*buffer;
	char	c[11];
	int		ret;

	buffer = NULL;
	ft_putstr_fd((char *)prompt, 1);
	while (1)
	{
		ret = read(STDIN_FILENO, c, 10);
		if (ret == ERROR)
			break ;
		c[ret] = '\0';
		if (ret == 1)
		{
			ret = ms_handle_simple_char(&buffer, c[0]);
			if (ret == ERROR)
				return (NULL);
			if (ret == LINE_END)
				break ;
		}
		else if (ms_handle_escape_sequence(&buffer, c) == ERROR)
			return (NULL);
	}
	return (buffer);
}