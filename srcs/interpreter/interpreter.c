/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:55:28 by twagner           #+#    #+#             */
/*   Updated: 2021/11/13 10:00:06 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "parser.h"

/*
** INTERPRETER
** The interpreter browse the AST in a certain order and push the arguments
** to the right executer (pipeline, command, simple command)
*/

static int	ms_search_ast(t_node *node, int needle, int nb)
{
	if (!node)
		return (nb);
	if (node->type == needle)
		++nb;
	nb = ms_search_ast(node->left, needle, nb);
	nb = ms_search_ast(node->right, needle, nb);
	return (nb);
}

int	ms_execute_ast(t_node *ast, char **envp)
{
	if (!ast)
		return (EXIT_FAILURE);
	if (ms_search_ast(ast, A_PIPE, 0))
	{
		if (ms_exec_comb_command(ast, envp, \
			ms_search_ast(ast, A_PIPE, 0)) == ERROR)
			return (EXIT_FAILURE);
	}
	else if (ms_exec_simple_command(ast, envp) == ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
