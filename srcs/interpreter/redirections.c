/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:05:38 by twagner           #+#    #+#             */
/*   Updated: 2021/12/26 09:30:22 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

void	ms_handle_here_doc(t_node *node)
{
	(void)node;
}

void	ms_handle_ret_append(t_node *node)
{
	int	fd;

	fd = open(node->right->data, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == ERROR)
	{
		perror("minishell");
		exit(1);
	}
	if (dup2(1, fd) == ERROR)
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

	printf("DATA : %s\n", node->right->data);
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
	if (!node)
		return ;
	ms_do_redirections(node->left);
	ms_do_redirections(node->right);
	if (node->type == A_PIPE)
		return ;
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
