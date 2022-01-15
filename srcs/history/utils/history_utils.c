/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:28:51 by twagner           #+#    #+#             */
/*   Updated: 2022/01/15 14:21:41 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

t_history	*ms_histo_new(char *data)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = B_NEW;
	new->data = ft_strdup(data);
	if (data && !new->data)
	{
		free(new);
		return (NULL);
	}
	new->saved_data = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

void	ms_histo_insert_front(t_history **histo, t_history *insert, int type)
{
	if (insert)
	{
		while (*histo && (*histo)->previous)
			*histo = (*histo)->previous;
		if (*histo)
		{
			insert->type = type;
			insert->next = (*histo);
			(*histo)->previous = insert;
			*histo = insert;
		}
		else
		{
			insert->type = type;
			*histo = insert;
		}
	}
}

void	ms_histo_del_one(t_history **histo, t_history **begin)
{
	t_history	*to_clear;
	t_history	*previous;
	t_history	*next;

	if (*histo)
	{
		previous = (*histo)->previous;
		next = (*histo)->next;
		to_clear = *histo;
		if (previous)
			previous->next = next;
		if (next)
			next->previous = previous;
		free(to_clear->data);
		free(to_clear->saved_data);
		free(to_clear);
		*histo = previous;
		if (!*histo)
		{
			*histo = next;
			*begin = next;
		}
	}
}

/*
** FREE ALL HISTORY
*/

void	ms_histo_clear(t_history *histo)
{
	t_history	*next;
	t_history	*previous;

	while (histo && histo->next)
	{
		next = histo->next->next;
		free(histo->next->data);
		free(histo->next->saved_data);
		free(histo->next);
		histo->next = next;
	}
	while (histo && histo->previous)
	{
		previous = histo->previous->previous;
		free(histo->previous->data);
		free(histo->previous->saved_data);
		free(histo->previous);
		histo->previous = previous;
	}
	if (histo)
	{
		free(histo->data);
		free(histo->saved_data);
		free(histo);
	}
}

/*
** CLEAN HISTORY BEFORE RETURNING CMD LINE
** - Removes Temporary "B_NEW" entry
** - Restore saved history entry if it has been modified then used as a new cmd
** - Save all modified history entries
** - Set the history pointer to the first item
*/

void	ms_histo_clean(t_history **histo)
{
	t_history	*begin;

	while (*histo && (*histo)->previous)
		*histo = (*histo)->previous;
	begin = *histo;
	while (*histo)
	{
		if ((*histo)->type == B_NEW)
			ms_histo_del_one(histo, &begin);
		if (*histo && (*histo)->type == B_HISTO_RESTORE)
		{
			free((*histo)->data);
			(*histo)->data = ft_strdup((*histo)->saved_data);
			(*histo)->type = B_HISTO;
		}
		else if (*histo)
		{
			free((*histo)->saved_data);
			(*histo)->saved_data = ft_strdup((*histo)->data);
		}
		if (*histo)
			*histo = (*histo)->next;
	}
	*histo = begin;
}
