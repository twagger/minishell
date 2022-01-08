/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:05:38 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 14:58:32 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** HERE DOC
** This function handle the here doc operator
*/

int	ms_handle_here_doc(t_node *node)
{
	(void)node;
	return (0);
}

/*
** FILE REDIRECTIONS
** The functions below handle file redirection (>, <, >>)
** Don't exit if simple command
*/

int	ms_handle_ret_append(t_node *node)
{
	int	fd;

	fd = open(node->right->right->data, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == ERROR)
	{
		perror(node->right->right->data);
		return (ERROR);
	}
	if (dup2(fd, 1) == ERROR)
	{
		perror("minishell");
		return (ERROR);
	}
	return (0);
}

int	ms_handle_ret_from(t_node *node)
{
	int	fd;

	fd = open(node->right->right->data, O_RDONLY);
	if (fd == ERROR)
	{
		perror(node->right->right->data);
		return (ERROR);
	}
	if (dup2(fd, 0) == ERROR)
	{
		perror("minishell");
		return (ERROR);
	}
	return (0);
}

int	ms_handle_ret_to(t_node *node)
{
	int	fd;

	fd = open(node->right->right->data, O_RDWR | O_CREAT, 0666);
	if (fd == ERROR)
	{
		perror(node->right->right->data);
		return (ERROR);
	}
	if (dup2(fd, 1) == ERROR)
	{
		perror("minishell");
		return (ERROR);
	}
	return (0);
}

/*
** REDIRECTIONS
** This command will execute the redirection before launching the command.
*/

int	ms_do_redirections(t_node *node, int ret)
{
	if (!node || (node && node->type == A_PIPE))
		return (ret);
	ret = ms_do_redirections(node->left, ret);
	ret = ms_do_redirections(node->right, ret);
	if (ret == ERROR)
		return (ERROR);
	if (node->reduc == R_IO_FILE)
	{
		if (node->left->type == T_RED_TO)
			ret = ms_handle_ret_to(node);
		if (node->left->type == T_RED_FROM)
			ret = ms_handle_ret_from(node);
		if (node->left->type == T_DGREAT)
			ret = ms_handle_ret_append(node);
	}
	if (node->reduc == R_IO_HERE)
		ret = ms_handle_here_doc(node);
	return (ret);
}
