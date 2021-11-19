/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:28:51 by twagner           #+#    #+#             */
/*   Updated: 2021/11/16 15:46:59 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	ms_is_new_in_histo(t_history **histo)
{
	int			res;
	t_history	*begin;

	res = 0;
	begin = *histo;
	if (!*histo)
		return (res);
	while ((*histo)->previous)
		*histo = (*histo)->previous;
	while (*histo)
	{
		if ((*histo)->type == B_NEW)
			res = 1;
		*histo = (*histo)->next;
	}
	*histo = begin;
	return (res);
}

void	ms_histo_clean(t_history **histo)
{
	t_history	*begin;

	ms_histo_rewind(histo);
	begin = *histo;
	while (*histo)
	{
		if ((*histo)->type == B_NEW)
			ms_histo_del_one(histo, &begin);
		if ((*histo)->type == B_HISTO_RESTORE)
		{
			free((*histo)->data);
			(*histo)->data = (*histo)->saved_data;
			(*histo)->saved_data = NULL;
			(*histo)->type = B_HISTO;
		}
		else
		{
			free((*histo)->saved_data);
			(*histo)->saved_data = ft_strdup((*histo)->data);
		}
		if (*histo)
			*histo = (*histo)->next;
	}
	*histo = begin;
}
