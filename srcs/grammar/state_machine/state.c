/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:53:25 by twagner           #+#    #+#             */
/*   Updated: 2021/10/24 11:33:32 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_machine.h"

// free state
// free transitions
// free state machine

t_state	*ms_new_state(int num, t_transition **actions, t_transition **gotos)
{
	t_state	*new;

	new = (t_state *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->num = num;
	new->actions = actions;
	new->gotos = gotos;
	return (new);
}

t_transition *ms_new_transition(int state, int event, int action, int next)
{
	t_transition	*new;

	new = (t_transition *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->state = state;
	new->event = event;
	new->action = action;
	new->next = next;
	return (new);
}

/*
** INIT STATE MACHINE
**  Boucler sur le fichier "automaton"
**	- compter le nombre de lignes pour un etat avec actions
**	- compter le nombre de lignes pout un etat sans actions (-1)
**  - malloc deux collections de transitions avec la bonne taille et creer les transitions
**	- creer l'etat et lui rattacher les collections de transition
**	- lire le fichier sur l'etat suivant, jusqu'a la fin du fichier
*/