/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:44:36 by twagner           #+#    #+#             */
/*   Updated: 2021/10/16 10:10:04 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	//Parcourir envp pour voir si la variable est dans la liste
	//Si pas dans la liste, return
	//Si dans la liste
	//malloc un char ** de la taille de envp - 1 + NULL
	//strdup tous les elements de envp SAUF celui a supprimer
	//free envp si ce n'est pas l'original
	//retourner le nouveau char **

	return (0);
}
