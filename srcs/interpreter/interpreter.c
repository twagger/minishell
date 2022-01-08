/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2022/01/08 14:35:15 by twagner          ###   ########.fr       */
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
	int	nb;
	int	fd[2];

	if (!ast)
		return (1);
	fd[0] = -1;
	nb = ms_search_ast(ast, A_PIPE, 0);
	if (nb)
		return (ms_exec_pipeline(ast, exit_code, nb));
	ms_save_std_fd((int *)fd);
	if (ms_do_redirections(ast, 0) == ERROR)
		return (1);
	return (ms_exec_simple_command(ast, exit_code, fd));
}
