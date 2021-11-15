/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:28:51 by twagner           #+#    #+#             */
/*   Updated: 2021/11/15 22:06:41 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	ms_is_new_in_histo(t_history **histo)
{
	int			res;
	t_history	*begin;

	res = 0;
	begin = *histo;
	ms_histo_rewind(histo);
	while (*histo)
	{
		if ((*histo)->type == B_NEW)
			res = 1;
		*histo = (*histo)->next;
	}
	*histo = begin;
	return (res);
}

t_history	*ms_histo_new(void *data)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = B_NEW;
	new->data = data;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

void	ms_histo_insert_front(t_history **histo, t_history *insert, int type)
{
	if (insert)
	{
		if (*histo)
		{
			insert->type = type;
			insert->next = *histo;
			(*histo)->previous = insert;
			*histo = insert;
		}
		else
			*histo = insert;
	}
}

void	ms_histo_rewind(t_history **histo)
{
	if (*histo)
	{
		while ((*histo)->previous)
			*histo = (*histo)->previous;
	}
}

void	ms_histo_clear(t_history *histo)
{
	t_history	*next;
	t_history	*previous;

	while (histo && histo->next)
	{
		next = histo->next->next;
		free(histo->next->data);
		free(histo->next);
		histo->next = next;
	}
	while (histo && histo->previous)
	{
		previous = histo->previous->previous;
		free(histo->previous->data);
		free(histo->previous);
		histo->previous = previous;
	}
	if (histo)
	{
		free(histo->data);
		free(histo);
	}
}
