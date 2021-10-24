/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 10:35:57 by twagner           #+#    #+#             */
/*   Updated: 2021/10/24 11:53:47 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "state_machine.h"

/*
** LR Parser
** - Etat courant = 0
** - regarder le premier mot de la liste chainee des tokens (input)
** - regarder si le mot est defini comme "event" sur l'etat courant
** - si oui, realiser l'action associee et changer d'etat
** - lorsqu'on fait une reduction, revenir a l'etat d'avant pour savoir ou aller ensuite
** - lorsqu'on fait une reduction, creer un noeud de la branche du parsing tree
** 	> On doit pouvoir creer l'ast directement avec de bonnes regles ici
*/

void	*ms_parser(t_token *tok_list)
{
	t_token *begin;

	begin = tok_list;
	while (tok_list)
	{
		
		tok_list = tok_list->next;
	}
}
