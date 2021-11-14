/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:28:51 by twagner           #+#    #+#             */
/*   Updated: 2021/11/14 09:55:12 by twagner          ###   ########.fr       */
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

t_history	*ms_histo_last(t_history *histo)
{
	while (histo && histo->next)
		histo = histo->next;
	return (histo);
}

void	ms_histo_insert_back(t_history **histo, t_history *insert)
{
	t_history	*last;

	if (insert)
	{
		last = ms_histo_last(*histo);
		if (last)
		{
			last->next = insert;
			insert->previous = last;
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
