/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 10:07:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 11:50:08 by twagner          ###   ########.fr       */
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

int	ms_add_char(char **buffer, char c)
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

char	*ms_del_char(char **buffer, int index)
{
	int		i;
	int		j;
	char	*new;

	if (!buffer)
		return (NULL);
	new = (char *)malloc(sizeof(*new) * ft_strlen(*buffer));
	if (!new)
	{
		free(*buffer);
		return (NULL);
	}
	j = 0;
	i = -1;
	while ((*buffer)[++i])
	{
		if (i != index)
			new[j++] = (*buffer)[i];
	}
	new[j] = '\0';
	free(*buffer);
	return (new);
}
