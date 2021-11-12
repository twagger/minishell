/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:38:14 by twagner           #+#    #+#             */
/*   Updated: 2021/11/12 11:24:25 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

t_arglist	*ms_arglist_new(void *data, int type)
{
	t_arglist	*new;

	new = (t_arglist *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = type;
	new->data = data;
	new->next = NULL;
	return (new);
}

t_arglist	*ms_arglist_last(t_arglist *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	ms_arglistadd_back(t_arglist **alst, t_arglist *new)
{
	if (*alst)
		ms_arglist_last(*alst)->next = new;
	else
		*alst = new;
}

void	ms_arglistadd_front(t_arglist **alst, t_arglist *new)
{
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void	ms_arglist_clear(t_arglist **lst)
{
	t_arglist	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = next;
	}
	lst = NULL;
}
