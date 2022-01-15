/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2022/01/15 17:17:40 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** INTERPRETER
** The interpreter browse the AST in a certain order and push the arguments
** to the right executer (pipeline, command, simple command)
*/

static int	ms_handle_heredoc(\
	t_node *ast, int **heredoc_fds, int *interrupt, t_garbage_coll *garcol)
{
	int	nb;

	nb = ms_search_ast(ast, A_DLESS, 0);
	if (nb)
	{
		ms_activate_hd_signal_handler();
		*heredoc_fds = ms_do_heredoc(ast, nb, interrupt);
		if (!*heredoc_fds)
			return (ERROR);
		garcol->heredoc_fds = *heredoc_fds;
		ms_restore_default_signals();
		dup2((*heredoc_fds)[nb], STDIN_FILENO);
		close((*heredoc_fds)[nb]);
		(*heredoc_fds)[nb] = -1;
	}
	return (0);
}

int	ms_search_ast(t_node *node, int needle, int nb)
{
	if (!node)
		return (nb);
	if (node->type == needle)
		++nb;
	nb = ms_search_ast(node->left, needle, nb);
	nb = ms_search_ast(node->right, needle, nb);
	return (nb);
}

int	ms_execute_ast(t_node *ast, t_garbage_coll *garcol)
{
	int	ret;
	int	nb;
	int	*heredoc_fds;
	int	fd[2];
	int	interrupt;

	fd[0] = -1;
	ret = 1;
	interrupt = 0;
	heredoc_fds = NULL;
	if (ms_handle_heredoc(ast, &heredoc_fds, &interrupt, garcol) == ERROR)
		return (ERROR);
	if (!interrupt)
	{
		nb = ms_search_ast(ast, A_PIPE, 0);
		if (nb)
			ret = ms_exec_pipeline(ast, nb, heredoc_fds, garcol);
		else
		{
			ms_save_std_fd((int *)fd);
			if (ms_do_redirections(ast, 0, heredoc_fds) != ERROR)
				ret = ms_exec_simple_command(ast, fd, garcol);
		}
	}
	return (ms_clear_heredoc(heredoc_fds, ret));
}
