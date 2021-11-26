/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 10:07:03 by twagner           #+#    #+#             */
/*   Updated: 2021/11/26 16:16:55 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char	ms_ctrl_key(char key)
{
	return (key & 0x1f);
}

/*
** ADD A CHAR TO AN EXISTING (OR NEW) HISTORY ENTRY
*/

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

/*
** REMOVE A CHAR FROM AN EXISTING HISTORY ENTRY
*/

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
