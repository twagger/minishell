/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:28:51 by twagner           #+#    #+#             */
/*   Updated: 2021/11/14 11:58:02 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

t_history	*ms_histo_new(void *data)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->data = data;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

void	ms_histo_insert_front(t_history **histo, t_history *insert)
{
	if (insert)
	{
		if (*histo)
		{
			insert->next = *histo;
			(*histo)->previous = insert;
			*histo = insert;
		}
		else
			*histo = insert;
	}
}

void	ms_histo_clear(t_history *histo)
{
	t_history	*next;

	while (histo)
	{
		next = histo->next;
		free(histo->data);
		free(histo);
		histo = next;
	}
}
