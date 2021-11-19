/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 10:07:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 12:38:16 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char	ms_ctrl_key(char key)
{
	return (key & 0x1f);
}

int	ms_putchar(int i)
{
	char	c;

	c = (char)i;
	write(1, &c, 1);
	return (1);
}

void	ms_put_line(char *buffer, int cpos)
{
	(void)cpos;
	tputs(tgetstr("dl", NULL), 0, ms_putchar);
	ft_putstr_fd("\x1B[32mMinishell> \e[0m", 1);
	ft_putstr_fd(buffer, 1);
	tputs(tgetstr("rc", NULL), 0, ms_putchar);
	if (cpos != 0)
		tputs(tgoto(tgetstr("RI", NULL), 0, cpos), 0, ms_putchar);
}

int	ms_add_char(t_history **histo, char c, int where)
{
	char	curr;
	char	saved;
	size_t	len;

	len = ft_strlen((*histo)->data);
	(*histo)->data = ft_realloc((*histo)->data, len + 2);
	if (!(*histo)->data)
		return (ERROR);
	if (where == -1)
		((*histo)->data)[len] = c;
	else
	{
		saved = c;
		while (where < (int)len + 1)
		{
			curr = ((*histo)->data)[where];
			((*histo)->data)[where] = saved;
			saved = curr;
			++where;
		}
	}	
	((*histo)->data)[len + 1] = '\0';
	return (EXIT_SUCCESS);
}

char	*ms_del_char(t_history **histo, int index)
{
	int		i;
	int		j;
	char	*new;

	if (!(*histo)->data)
		return (NULL);
	new = (char *)malloc(sizeof(*new) * ft_strlen((*histo)->data));
	if (!new)
	{
		free((*histo)->data);
		return (NULL);
	}
	j = 0;
	i = -1;
	while ((*histo)->data[++i])
	{
		if (i != index)
			new[j++] = ((*histo)->data)[i];
	}
	new[j] = '\0';
	free((*histo)->data);
	return (new);
}
