/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:05:38 by twagner           #+#    #+#             */
/*   Updated: 2021/12/24 11:49:07 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** REDIRECTIONS
** This command will execute the redirection before launching the command.
*/
void	ms_do_redirections(t_node *node, char **envp, int exit_code)
{
	if (!node)
		return ;
	ms_do_redirections(node->left, envp, exit_code);
	ms_do_redirections(node->right, envp, exit_code);
	if (node->type == R_IO_FILE)
	{
		// open file
		// if error > perror & exit
		// dup2 fd1 > file
		// la commande s'arrete si un fichier n'est pas ok niveau permission
	}
	if (node->type == R_IO_HERE)
	{
		// dup2 fd0 > file
		// la commande s'arrete si un fichier n'est pas ok niveau permission
	}
	if (node->type == A_DGREAT)
	{
		node = NULL;
	}
}
