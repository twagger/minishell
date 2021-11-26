/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:15:50 by twagner           #+#    #+#             */
/*   Updated: 2021/11/26 20:39:12 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	ms_putchar(int i)
{
	char	c;

	c = (char)i;
	write(1, &c, 1);
	return (1);
}

void	ms_refresh_line(char *buffer, int len)
{
	int	i;

	tputs(tgetstr("rc", NULL), 0, ms_putchar);
	i = -1;
	while (++i < len)
		ms_delete_char();
	if (buffer)
	{
		while (*buffer)
		{
			ms_insert_char(*buffer);
			++buffer;
		}
	}
}

void	ms_insert_char(char c)
{
	tputs(tgetstr("im", NULL), 0, ms_putchar);
	tputs(tgetstr("ic", NULL), 0, ms_putchar);
	ft_putchar_fd(c, 1);
	tputs(tgetstr("ei", NULL), 0, ms_putchar);
}

void	ms_delete_char(void)
{
	tputs(tgetstr("dm", NULL), 0, ms_putchar);
	tputs(tgetstr("dc", NULL), 0, ms_putchar);
	tputs(tgetstr("ed", NULL), 0, ms_putchar);
}
