/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:05:38 by twagner           #+#    #+#             */
/*   Updated: 2022/01/14 10:28:37 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** HERE DOC
** This function handle the here doc operator
*/

static int	ms_handle_here_doc(int *hd_fds)
{
	static int	num = 0;
	int			fd;

	fd = hd_fds[num];
	if (hd_fds[num + 1] == -1)
		num = 0;
	else
		++num;
	if (dup2(fd, STDIN_FILENO) == ERROR)
	{
		perror("minishell");
		return (ERROR);
	}
	return (0);
}

/*
** FILE REDIRECTIONS
** The functions below handle file redirection (>, <, >>)
** Don't exit if simple command
*/

static int	ms_handle_ret_append(t_node *node)
{
	int	fd;

	fd = open(node->right->right->data, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == ERROR)
	{
		perror(node->right->right->data);
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == ERROR)
	{
		perror("minishell");
		return (ERROR);
	}
	return (0);
}

static int	ms_handle_ret_from(t_node *node)
{
	int	fd;

	fd = open(node->right->right->data, O_RDONLY);
	if (fd == ERROR)
	{
		perror(node->right->right->data);
		return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == ERROR)
	{
		perror("minishell");
		return (ERROR);
	}
	return (0);
}

static int	ms_handle_ret_to(t_node *node)
{
	int	fd;

	fd = open(node->right->right->data, O_RDWR | O_CREAT, 0666);
	if (fd == ERROR)
	{
		perror(node->right->right->data);
		return (ERROR);
	}
	if (dup2(fd, STDOUT_FILENO) == ERROR)
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

int	ms_do_redirections(t_node *node, int ret, int *hd_fds)
{
	if (!node || (node && node->type == A_PIPE))
		return (ret);
	ret = ms_do_redirections(node->left, ret, hd_fds);
	ret = ms_do_redirections(node->right, ret, hd_fds);
	if (ret == ERROR)
		return (ERROR);
	if (node->reduc == R_IO_FILE)
	{
		if (node->left->type == A_RED_TO)
			ret = ms_handle_ret_to(node);
		if (node->left->type == A_RED_FROM)
			ret = ms_handle_ret_from(node);
		if (node->left->type == A_DGREAT)
			ret = ms_handle_ret_append(node);
	}
	if (node->reduc == R_IO_HERE)
		ret = ms_handle_here_doc(hd_fds);
	return (ret);
}
