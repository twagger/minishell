/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2022/01/09 09:14:11 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

/*
** INTERPRETER
** The interpreter browse the AST in a certain order and push the arguments
** to the right executer (pipeline, command, simple command)
*/

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

int	ms_execute_ast(t_node *ast, int exit_code)
{
	int	ret;
	int	nb;
	int	*heredoc_fds;
	int	fd[2];

	fd[0] = -1;
	heredoc_fds = NULL;
	nb = ms_search_ast(ast, A_DLESS, 0);
	if (nb)
	{
		heredoc_fds = ms_do_heredoc(ast, nb);
		if (!heredoc_fds)
			return (1);
	}
	nb = ms_search_ast(ast, A_PIPE, 0);
	if (nb)
	{
		ret = ms_exec_pipeline(ast, exit_code, nb);
		return (ms_clear_heredoc(heredoc_fds, ret));
	}
	ms_save_std_fd((int *)fd);
	if (ms_do_redirections(ast, 0) == ERROR)
		return (ms_clear_heredoc(heredoc_fds, 1));
	ret = ms_exec_simple_command(ast, exit_code, fd);
	return (ms_clear_heredoc(heredoc_fds, ret));
}
