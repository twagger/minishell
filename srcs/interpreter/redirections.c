/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:05:38 by twagner           #+#    #+#             */
/*   Updated: 2021/12/27 10:22:39 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** HERE DOC
** This function handle the here doc operator
*/

void	ms_handle_here_doc(t_node *node)
{
	(void)node;
}

/*
** FILE REDIRECTIONS
** The functions below handle file redirection (>, <, >>)
*/

void	ms_handle_ret_append(t_node *node)
{
	int	fd;

	fd = open(node->right->data, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == ERROR)
	{
		perror("minishell");
		exit(1);
	}
	if (dup2(fd, 1) == ERROR)
	{
		perror("minishell");
		exit(1);
	}
}

void	ms_handle_ret_from(t_node *node)
{
	int	fd;

	fd = open(node->right->data, O_RDONLY);
	if (fd == ERROR)
	{
		perror("minishell");
		exit(1);
	}
	if (dup2(fd, 0) == ERROR)
	{
		perror("minishell");
		exit(1);
	}
}

void	ms_handle_ret_to(t_node *node)
{
	int	fd;

	fd = open(node->right->data, O_RDWR | O_CREAT, 0666);
	if (fd == ERROR)
	{
		perror("minishell");
		exit(1);
	}
	if (dup2(fd, 1) == ERROR)
	{
		perror("minishell");
		exit(1);
	}
}

/*
** REDIRECTIONS
** This command will execute the redirection before launching the command.
*/

void	ms_do_redirections(t_node *node)
{
	if (!node || (node && node->type == A_PIPE))
		return ;
	ms_do_redirections(node->left);
	ms_do_redirections(node->right);
	if (node->reduc == R_IO_FILE)
	{
		if (node->left->type == T_RED_TO)
			ms_handle_ret_to(node);
		if (node->left->type == T_RED_FROM)
			ms_handle_ret_from(node);
		if (node->left->type == T_DGREAT)
			ms_handle_ret_append(node);
	}
	if (node->reduc == R_IO_HERE)
		ms_handle_here_doc(node);
}
